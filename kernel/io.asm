[bits 32]

global inb
inb:
	mov dx, [esp + 4]
	in al, dx
	ret

global outb
outb:
	mov al, [esp + 8]
	mov dx, [esp + 4]
	out dx, al
	ret

global inw
inw:
	mov dx, [esp + 4]
	in ax, dx
	ret

global outw
outw:
	mov ax, [esp + 8]
	mov dx, [esp + 4]
	out dx, ax
	ret

; https://wiki.osdev.org/Inline_Assembly/Examples#I.2FO_access
global io_wait
io_wait:
	mov al, 0
	mov dx, 0x80
	out dx, al
	ret