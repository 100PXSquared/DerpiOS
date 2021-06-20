#include "screen.h"
#include "../io_wrappers.h"
#include "../utils.h"

// Calculate an offset from the video memory location to place a char
unsigned int get_vidmem_offset(const int col, const int row)
{
	return (row * COLS + col) * 2;
}

// Get the hardware cursor position
unsigned int get_cursor()
{
	port_byte_out(REG_SCREEN_CTRL, 14);                       // Set hardware ptr to lower byte
	unsigned int offset = port_byte_in(REG_SCREEN_DATA) << 8; // Get byte
	port_byte_out(REG_SCREEN_CTRL, 15);                       // Set hardware ptr to upper byte
	offset += port_byte_in(REG_SCREEN_DATA);                  // Get byte

	return offset * 2; // Convert chars to offset
}

// Set the hardware cursor position
void set_cursor(unsigned int offset)
{
	offset /= 2; // Convert offset to chars

	port_byte_out(REG_SCREEN_CTRL, 14);                           // Set hardware ptr to lower byte
	port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8)); // Set byte
	port_byte_out(REG_SCREEN_CTRL, 15);                           // Set hardware ptr to upper byte
	port_byte_out(REG_SCREEN_DATA, (unsigned char)offset);        // Set byte
}

// Disable the hardware cursor
void disable_cursor()
{
	// Set disable bit
	port_byte_out(REG_SCREEN_CTRL, 0x0a); // Cursor start register
	port_byte_out(REG_SCREEN_DATA, 0b00100000);
}

// Enable the hardware cursor
void enable_cursor()
{
	// Get maximum scan line
	port_byte_out(REG_SCREEN_CTRL, 0x09); // Maximum scan line register
	unsigned char max_scan_line = port_byte_in(REG_SCREEN_DATA) & 0b00011111;

	// Set cursor start
	port_byte_out(REG_SCREEN_CTRL, 0x0a); // Cursor start register
	port_byte_out(REG_SCREEN_DATA, (port_byte_in(REG_SCREEN_DATA) & 0b11000000) | (max_scan_line - 1));


	// Set cursor end to maximum
	port_byte_out(REG_SCREEN_CTRL, 0x0b); // Cursor end register
	port_byte_out(REG_SCREEN_DATA, (port_byte_in(REG_SCREEN_DATA) & 0b11100000) | max_scan_line);
}

// Clear the screen
void clear()
{
	unsigned char* ptr = (unsigned char*)VGA_ADDR;
	const unsigned char* maxoffset = ptr + COLS * ROWS * 2;
	for (; ptr < maxoffset; ptr++) {
		*ptr = (unsigned char)0;
		ptr++;
		*ptr = (unsigned char)DEFAULT_CHAR_FORMAT;
	}
	set_cursor(0);
}

// Scroll the screen up
void scroll(unsigned int* offset)
{
	unsigned int colsx2 = COLS * 2;
	if (*offset < colsx2 * ROWS) return;

	unsigned char* ptr = (unsigned char*)VGA_ADDR;

	int row;
	for (row = 0; row < ROWS; row++) {
		memcpy(
			ptr + get_vidmem_offset(0, row - 1),
			ptr + get_vidmem_offset(0, row),
			colsx2
		);
	}

	ptr += get_vidmem_offset(0, ROWS - 1);
	const unsigned char* maxoffset = ptr + colsx2;
	for (; ptr < maxoffset; ptr++) *ptr = (unsigned char)0;

	*offset -= colsx2;
}

// Put a char in video memory
void putchar(const char chr, const int col,  const int row, char attrs)
{
	unsigned int offset;
	if (col >= 0 && row >= 0) offset = get_vidmem_offset(col, row);
	else offset = get_cursor();

	if (chr == '\n') offset = get_vidmem_offset(79, offset / (2 * COLS));
	else {
		unsigned char* vidptr = (unsigned char*)VGA_ADDR + offset;
		*vidptr = chr;
		*(vidptr + 1) = attrs;
	}

	offset += 2;
	scroll(&offset);
	set_cursor(offset);
}

// Put a string in video memory
void putstr(const char* str, const int col, const int row)
{
	if (col >= 0 && row >= 0) set_cursor(get_vidmem_offset(col, row));

	const char* ptr;
	for (ptr = str; *ptr != '\0'; ptr++) putchar(*ptr, -1, -1, DEFAULT_CHAR_FORMAT);
}

// General purpose print
void print(const char* str)
{
	putstr(str, -1, -1);
}