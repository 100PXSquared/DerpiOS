#ifndef IO_WRAPPERS
#define IO_WRAPPERS

// Read byte
unsigned char inb(unsigned short port);

// Write byte
void outb(unsigned short port, unsigned char byte);

// Read word
unsigned short inw(unsigned short port);

// Write word
void outw(unsigned short port, unsigned short word);

#endif
