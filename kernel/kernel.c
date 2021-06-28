#include "utils.h"
#include "idt.h"
#include "pic.h"
#include "io_wrappers.h"
#include "drivers/screen.h"
#include "drivers/serial.h"
#include "drivers/keyboard.h"

void register_idt_entry(
	const unsigned int handler_addr, const unsigned char attributes,
	const unsigned char idx, struct idt_entry idt_tbl[256]
)
{
	struct idt_entry entry;
	entry.offset_high = handler_addr >> 16;
	entry.offset_low = handler_addr & 0x0000ffff;
	entry.segment_selector = 0x0008;
	entry.attrs = attributes;
	idt_tbl[idx] = entry;
}

#define REGISTER_INTERRUPT(idx) register_idt_entry((unsigned int)interrupt_handler_##idx, 0x8e, idx, idt_tbl)

void setup_interrupts()
{
	struct idt_entry idt_tbl[256];

	// CPU Exceptions
	REGISTER_INTERRUPT(0);
	REGISTER_INTERRUPT(1);
	REGISTER_INTERRUPT(2);
	REGISTER_INTERRUPT(3);
	REGISTER_INTERRUPT(4);
	REGISTER_INTERRUPT(5);
	REGISTER_INTERRUPT(6);
	REGISTER_INTERRUPT(7);
	REGISTER_INTERRUPT(8);
	// 9 outdated
	REGISTER_INTERRUPT(10);
	REGISTER_INTERRUPT(11);
	REGISTER_INTERRUPT(12);
	REGISTER_INTERRUPT(13);
	REGISTER_INTERRUPT(14);
	// 15 reserved
	REGISTER_INTERRUPT(16);
	REGISTER_INTERRUPT(17);
	REGISTER_INTERRUPT(18);
	REGISTER_INTERRUPT(19);
	REGISTER_INTERRUPT(20);
	// 21-29 reserved
	REGISTER_INTERRUPT(30);
	// 31 reserved

	// PIC Interrupts
	REGISTER_INTERRUPT(33); // Keyboard

	struct idt_ptr idt;
	idt.size = sizeof(struct idt_entry) * 256 - 1;
	idt.ptr = idt_tbl;
	load_idt(idt);

	// Initialise PICs
	init_pic();
}

int main()
{
	serial_init(SERIAL_COM1, 1);
	keyboard_init();

	setup_interrupts();

	clear();
	enable_cursor();
	print("DerpiOS Kernel - v0.1.0\n");
	print("Screen driver loaded!\n");

	while (1) {
		char kb_buffer[KEYBOARD_BUFFER_SIZE];
		memset(kb_buffer, '\0', KEYBOARD_BUFFER_SIZE);
		kb_read_buffer(kb_buffer);
		print(kb_buffer);
	}

	return 0;
}
