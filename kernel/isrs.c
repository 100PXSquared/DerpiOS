#include "idt.h"
#include "drivers/serial.h"

void interrupt_handler(struct cpu_state cpu, struct stack_state stack, unsigned int interrupt)
{
	serial_print("ISR called\r\n", SERIAL_COM1);
}