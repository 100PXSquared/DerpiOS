#ifndef SCREEN
#define SCREEN

#define VGA_ADDR 0xb8000
#define ROWS 25
#define COLS 80

#define DEFAULT_CHAR_FORMAT 0x0f

// VGA IO Registers
#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

// Clear the screen
void clear();

// General purpose print
void print(const char* str);

// Disable cursor
void disable_cursor();

// Enable cursor
void enable_cursor();

#endif