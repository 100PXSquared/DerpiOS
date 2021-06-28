#ifndef PIC
#define PIC

// IO addresses
#define PIC1_COMM 0x20
#define PIC1_DATA 0x21
#define PIC2_COMM 0xa0
#define PIC2_DATA 0xa1

// Commands
#define PIC_EOI 0x20 // End of interrupt

// IDT addresses
#define PIC1_START 0x20
#define PIC2_START 0x28
#define PIC2_END   0x2f

void init_pic();

#endif
