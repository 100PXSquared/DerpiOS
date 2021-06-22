#include "idt.h"
#include "utils.h"
#include "drivers/serial.h"

void interrupt_handler(struct cpu_state cpu, unsigned int interrupt, struct stack_state stack)
{
	if (interrupt < 31) {
		const char* pretty_messages[31] = {
			"Divide-by-zero Error",
			"Debug",
			"Non-maskable Interrupt",
			"Breakpoint",
			"Overflow",
			"Bound Range Exceeded",
			"Invalid Opcode",
			"Device Not Available",
			"Double Fault",
			"", // Outdated
			"Invalid TSS",
			"Segment Not Present",
			"Stack-Segment Fault",
			"General Protection Fault",
			"Page Fault",
			"", // Reserved
			"x87 Floating-Point Exception",
			"Alignment Check",
			"Machine Check",
			"SIMD Floating-Point Exception",
			"Virtualization Exception",
			"","","","","","","","","", // Reserved
			"Security Exception"
		};

		serial_print("===== EXCEPTION =====\r\n", SERIAL_COM1);
		serial_print(pretty_messages[interrupt], SERIAL_COM1);
		serial_print("\r\n", SERIAL_COM1);

		char num_buffer[20];
		memset(num_buffer, 0, 20);

		serial_print("Error code: ", SERIAL_COM1);
		uint_to_string(stack.error_code, num_buffer);
		serial_print(num_buffer, SERIAL_COM1);
		serial_print("\r\n", SERIAL_COM1);

		//memset(num_buffer, 0, 20); ready for if I need to print more debug info

		serial_print("\r\n", SERIAL_COM1);
	}

	#ifdef DEBUG
	while (1); // If we're in debug mode, then hang the system here so we can check the serial monitor
	#endif
}