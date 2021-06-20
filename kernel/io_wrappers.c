#include "io_wrappers.h"

// Read byte
unsigned char port_byte_in(unsigned short port)
{
	unsigned char ret;
	__asm__("in %%dx, %%al" : "=a" (ret) : "d" (port));
	return ret;
}

// Write byte
void port_byte_out(unsigned short port, unsigned char byte)
{
	__asm__("out %%al, %%dx" : :"a" (byte), "d" (port));
}

// Read word
unsigned short port_word_in(unsigned short port)
{
	unsigned short ret;
	__asm__("in %%dx, %%ax" : "=a" (ret) : "d" (port));
	return ret;
}

// Write word
void port_word_out(unsigned short port, unsigned short word)
{
	__asm__("out %%ax, %%dx" : :"a" (word), "d" (port));
}