#include "keyboard.h"
#include "serial.h"
#include "../io_wrappers.h"
#include "../utils.h"

static char buffer[KEYBOARD_BUFFER_SIZE];
static unsigned int ptr;
static unsigned char modifiers;

void keyboard_init()
{
	ptr = 0;
	memset(buffer, '\0', KEYBOARD_BUFFER_SIZE);
	modifiers = 0;
}

char translate_scancode(const unsigned char scancode)
{
	const char* scancode_to_ascii = "  1234567890-=\b\tqwertyuiop[]  asdfghjkl;'` #zxcvbnm,./ *                  -   +       \\";
	return scancode_to_ascii[scancode];
}

void handle_scancode()
{
	const unsigned char scancode = inb(KEYBOARD_DATA);

	serial_print("Scancode received: ", SERIAL_COM1);
	serial_print(to_hex_str(scancode), SERIAL_COM1);
	serial_print("\r\n", SERIAL_COM1);

	if (scancode == 0xe0) { // Extended
		//modifiers |= 0b00000001;
		return;
	}

	if (modifiers & 0b00000001) { // If the extended code flag is set
		serial_print("Extended scancodes not supported (yet)\r\n", SERIAL_COM1);
		return;
	}

	switch (scancode) {
		case 0x01: // Escape
			break;
		case 0x1c: // Enter
			buffer[ptr++] = '\r';
			if (ptr > KEYBOARD_BUFFER_SIZE - 1) ptr = 0;
			buffer[ptr++] = '\n';
			if (ptr > KEYBOARD_BUFFER_SIZE - 1) ptr = 0;
			break;
		case 0x2a: // Left Shift
			break;
		case 0x36: // Right Shift
			break;
		case 0x38: // Left Alt
			break;
		case 0x3a: // Caps Lock
			break;
		case 0x45: // Num Lock
			break;
		case 0x46: // Scroll Lock
			break;
		case 0x54: // Print Screen
			break;
		default:
			if (scancode < 0x57) {
				if (scancode > 0x3a) { 
					if (scancode < 0x45) { // F1-F10
						break;
					}
					if (scancode < 0x54 && scancode != 0x4a && scancode != 0x4e) { // Numpad, except - and + which are always those chars
						break;
					}
				}

				// Actual characters
				buffer[ptr++] = translate_scancode(scancode);
				if (ptr > KEYBOARD_BUFFER_SIZE - 1) ptr = 0;
			} else if (scancode < 0x59) { // F11 and F12
				break;
			}
	}
}

void kb_read_buffer(char out[KEYBOARD_BUFFER_SIZE])
{
	// Read buffer into a string (backwards)
	char reversed[KEYBOARD_BUFFER_SIZE];
	memset(reversed, '\0', KEYBOARD_BUFFER_SIZE);

	unsigned int i = ptr - 1, j = KEYBOARD_BUFFER_SIZE - 1;
	if (i < 0) i = KEYBOARD_BUFFER_SIZE - 1;
	while (1) {
		reversed[j] = buffer[i];

		j--;
		i--;
		if (i < 0) i = KEYBOARD_BUFFER_SIZE - 1;

		if (buffer[i] == '\0' || i == ptr) break;
	}

	// Reverse backwards string
	j = 0;
	for (i = 0; i < KEYBOARD_BUFFER_SIZE; i++) {
		if (reversed[i] == '\0') continue;
		out[j] = reversed[i];
	}

	// Clear buffer
	ptr = 0;
	memset(buffer, '\0', KEYBOARD_BUFFER_SIZE);
}