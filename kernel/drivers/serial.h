#ifndef SERIAL
#define SERIAL

#define SERIAL_COM1 0x3f8

#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base) (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base) (base + 5)

#define SERIAL_LINE_ENABLE_DLAB 0x80

// Initialise COM port as plain serial output
void serial_init(unsigned int com, unsigned short divisor);

// Print ASCII to COM port (must be initialised with serial_init first)
void serial_print(const char* str, unsigned int com);

#endif