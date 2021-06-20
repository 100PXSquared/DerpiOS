; Takes a char pointer stored in bx and prints it using BIOS interrupts
print:
	pusha

	mov ah, 0x0e ; teletype text mode

	; while next char != 0, move the char to al and trigger interrupt
	.loop:
		mov al, [bx] ; move char to al
		cmp al, 0    ; check if char is null
		je .end      ; if char is null then jump to end
		int 0x10     ; otherwise, send interrupt
		add bx, 1    ; increment char pointer
		jmp .loop
	.end:

	popa
	ret

; Takes a 16 bit hexadecimal value stored in dx and convert it to a string, printing said string
print_hex:
	pusha

	mov cx, dx     ; copy dx to cx for low nibbles
	shr cl, 4      ; right shift low bits to get high nibble
	shr ch, 4      ; right shift high bits to get high nibble
	and dx, 0x0f0f ; sets the high nibbles of dx's 2 bytes to 0

	; for each of the nibbles
	; if the nibble is > 0x9 then use the alpha offset
	; else use the numeric offset

	; Nibble 1
	cmp ch, 0x9         ; compare high nibble of high byte to 0x9 (the max numerical display value)
	jle .nibble1numeric ; if we're in the range 0-9 for this nibble (i.e. this can be displayed with a number), jump to the numeric ascii offset
		add ch, 0x57    ; add the offset to the lowercase alphabet section of ascii (0x61), minus 10 for the 10 values that are numerical
		jmp .nibble1end
	.nibble1numeric:
		add ch, 0x30    ; offset to numeric part of the ascii table
	.nibble1end:
		mov [HEX_PRINT_BUFFER+2], ch ; move the calculated ascii character into the print buffer

	; Nibble 2
	cmp dh, 0x9
	jle .nibble2numeric
		add dh, 0x57
		jmp .nibble2end
	.nibble2numeric:
		add dh, 0x30
	.nibble2end:
		mov [HEX_PRINT_BUFFER+3], dh

	; Nibble 3
	cmp cl, 0x9
	jle .nibble3numeric
		add cl, 0x57
		jmp .nibble3end
	.nibble3numeric:
		add cl, 0x30
	.nibble3end:
		mov [HEX_PRINT_BUFFER+4], cl

	; Nibble 4
	cmp dl, 0x9
	jle .nibble4numeric
		add dl, 0x57
		jmp .nibble4end
	.nibble4numeric:
		add dl, 0x30
	.nibble4end:
		mov [HEX_PRINT_BUFFER+5], dl

	; Print the buffer
	mov bx, HEX_PRINT_BUFFER
	call print

	popa
	ret

HEX_PRINT_BUFFER db "0x0000", 0 ; Buffer for print_hex
