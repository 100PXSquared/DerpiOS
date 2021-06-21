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
