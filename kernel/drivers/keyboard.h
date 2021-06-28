#ifndef KEYBOARD
#define KEYBOARD

#define KEYBOARD_DATA 0x60

#define KEYBOARD_BUFFER_SIZE 1024

void keyboard_init();

void handle_scancode();

void kb_read_buffer(char out[256]);

#endif