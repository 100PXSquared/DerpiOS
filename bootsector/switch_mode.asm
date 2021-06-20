[bits 16]
switch_to_protected:
	cli ; Disable interrupts
	lgdt [gdt_descriptor] ; Load global descriptor table

	; Set the switch bit in the control register
	mov eax, cr0
	or eax, 1b
	mov cr0, eax

	jmp CODE_SEG:init_protected

[bits 32]
init_protected:
	; Init segment registers
	mov ax, DATA_SEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	; Init stack positions
	mov ebp, 0x90000
	mov esp, ebp

	call ON_PROTECTED
