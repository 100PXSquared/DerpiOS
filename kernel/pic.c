#include "pic.h"
#include "io_wrappers.h"

void init_pic()
{
	// Tell the PICs we're configuring them
	outb(PIC1_COMM, 0x11);
	io_wait();
	outb(PIC2_COMM, 0x11);
	io_wait();

	// Give offsets
	outb(PIC1_DATA, PIC1_START);
	io_wait();
	outb(PIC2_DATA, PIC2_START);
	io_wait();

	// Set wiring config
	outb(PIC1_DATA, 4);
	io_wait();
	outb(PIC2_DATA, 2);
	io_wait();

	// Set environment info
	outb(PIC1_DATA, 1);
	io_wait();
	outb(PIC2_DATA, 1);
	io_wait();

	// Set masks
	outb(PIC1_DATA, 0b11111101);
	outb(PIC2_DATA, 0b11111111);
}