[bits 32]

global load_idt
load_idt:
	lidt [esp + 4]
	ret

%macro no_error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	push dword 0                 ; push 0 as error code
	push dword %1                ; push the interrupt number
	jmp common_interrupt_handler ; jump to the common handler
%endmacro

%macro error_code_interrupt_handler 1
global interrupt_handler_%1
interrupt_handler_%1:
	push dword %1                ; push the interrupt number
	jmp common_interrupt_handler ; jump to the common handler
%endmacro

[extern interrupt_handler]
common_interrupt_handler:
	; save the registers
	pushad

	; call the C function
	cld
	call interrupt_handler

	; restore the registers
	popad

	; restore the esp
	add esp, 8

	; return to the code that got interrupted
	iret

no_error_code_interrupt_handler 0