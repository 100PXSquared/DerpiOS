#include "utils.h"
#include "idt.h"
#include "drivers/screen.h"
#include "drivers/serial.h"

#define true 1
#define false 0
#define NULL (void*)0

void uint_to_string(unsigned int number, char out[20])
{
	char* ptr = out;

	unsigned int i;
	unsigned char hitnum = false;
	for (i = 0; i < 20; i++) {
		unsigned int digit = number;
		unsigned int place = 1;

		unsigned int j;
		for (j = 19 - i; j > 0; j--) {
			digit /= 10;
			place *= 10;
		}

		if (digit != 0) hitnum = true;
		
		if (hitnum) {
			*ptr = digit + 0x30;
			ptr++;
			number -= digit * place;
		}
	}
	if (!hitnum) *ptr = '0';
}

unsigned long long strlen(const char* str)
{
	if (str == NULL) return 0;

	const char* ptr;
	for (ptr = str; *ptr != '\0'; ptr++);
	return ptr - str;
}

int main()
{
	serial_init(SERIAL_COM1, 1);

	// Set up IDT
	struct idt_entry idt_tbl[256];

	// Divide by 0 interrupt
	struct idt_entry div_by_zero;
	div_by_zero.offset_high = (int)interrupt_handler_0 >> 16;
	div_by_zero.offset_low = (int)interrupt_handler_0 & 0x0000ffff;
	div_by_zero.segment_selector = 0x0008;
	div_by_zero.attrs = 0x8e;

	idt_tbl[0] = div_by_zero;

	struct idt_ptr idt;
	idt.size = sizeof(struct idt_entry) * 256 - 1;
	idt.ptr = idt_tbl;
	load_idt(idt);

	clear();
	enable_cursor();
	print("DerpiOS Kernel - v0.1.0\n");
	print("Screen driver loaded!\n");

	int x = 1/0; // Triggers the divide by 0 ISR

	return 0;
}
