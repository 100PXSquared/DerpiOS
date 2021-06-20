#ifndef IO_WRAPPERS
#define IO_WRAPPERS

// Read byte
unsigned char port_byte_in(unsigned short port);

// Write byte
void port_byte_out(unsigned short port, unsigned char byte);

// Read word
unsigned short port_word_in(unsigned short port);

// Write word
void port_word_out(unsigned short port, unsigned short word);

#endif