[bits 32]

global load_idt
load_idt:
	lidt [esp + 4]
	sti
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
	push eax
	push ebx
	push ecx
	push edx
	push edi
	push esi
	push ebp
	push esp

	; call the C function
	call interrupt_handler

	; restore the registers
	pop esp
	pop ebp
	pop esi
	pop edi
	pop edx
	pop ecx
	pop ebx
	pop eax

	; restore the esp
	add esp, 8

	; return to the code that got interrupted
	iret

; CPU Exceptions
no_error_code_interrupt_handler 0
no_error_code_interrupt_handler 1
no_error_code_interrupt_handler 2
no_error_code_interrupt_handler 3
no_error_code_interrupt_handler 4
no_error_code_interrupt_handler 5
no_error_code_interrupt_handler 6
no_error_code_interrupt_handler 7
error_code_interrupt_handler    8
; 9 outdated
error_code_interrupt_handler    10
error_code_interrupt_handler    11
error_code_interrupt_handler    12
error_code_interrupt_handler    13
error_code_interrupt_handler    14
; 15 reserved
no_error_code_interrupt_handler 16
error_code_interrupt_handler    17
no_error_code_interrupt_handler 18
no_error_code_interrupt_handler 19
no_error_code_interrupt_handler 20
; 21-29 reserved
error_code_interrupt_handler    30
; 31 reserved

; PIC Interrupts
no_error_code_interrupt_handler 33