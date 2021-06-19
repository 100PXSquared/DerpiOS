[org 0x7c00]
KERNEL_OFFSET equ 0x7e00

mov [BOOT_DRIVE], dl ; Copy drive number provided by BIOS to BOOT_DRIVE label

; Init stack pointer to safe memory
mov bp, 0x9000
mov sp, bp

; Print startup message
mov bx, MSG_BOOT
call print
mov bx, NEWLINE
call print

call load_kernel

call switch_to_protected

jmp $

%include "bootsector/utils.asm"
%include "bootsector/drive.asm"
%include "bootsector/gdt.asm"
%include "bootsector/switch_mode.asm"
%include "bootsector/utils_pm.asm"

[bits 16]
load_kernel:
	; Print status
	mov bx, MSG_LOADING_KERNEL
	call print
	mov bx, NEWLINE
	call print

	; Load from disk
	mov bx, KERNEL_OFFSET ; Set read pointer
	mov dh, 8             ; Sectors to load
	mov dl, [BOOT_DRIVE]  ; Disk to load from
	call disk_load

	ret

[bits 32]
ON_PROTECTED:
	mov ebx, MSG_PROTECTED_MODE
	call print_pm

	call KERNEL_OFFSET ; Run the kernel

	jmp $

; Globals
BOOT_DRIVE db 0

MSG_BOOT db "Loading DerpiOS...", 0
MSG_PROTECTED_MODE db "Switched to 32 bit protected mode", 0
MSG_LOADING_KERNEL db "Loading kernel...", 0
SPACE db 0x20, 0
NEWLINE db 0x0d, 0x0a, 0 ; CRLF

times 510-($-$$) db 0
dw 0xaa55