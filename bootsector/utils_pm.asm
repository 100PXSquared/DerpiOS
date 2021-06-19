[bits 32]
VIDEO_PTR equ 0xb8000
DEFAULT_COLOUR equ 0x0f

; Takes a char pointer stored in ebx and prints it using VGA text mode
print_pm:
	pusha
	mov edx, VIDEO_PTR ; Move VGA start ptr to edx

	.loop:
		mov al, [ebx]          ; move char to lower byte of a

		cmp al, 0           ; check if char is null
		je .end                ; if it is, break

		mov ah, DEFAULT_COLOUR ; move config to upper byte of a

		mov [edx], ax          ; move full VGA 2 byte char to video memory

		add ebx, 1             ; increment char pointer
		add edx, 2             ; increment video memory pointer (2 bytes due to VGA char size)

		jmp .loop
	.end:

	popa
	ret