#ifndef IDT
#define IDT

struct idt_entry
{
	unsigned short offset_low;
	unsigned short segment_selector;
	unsigned char reserved;
	unsigned char attrs; // P DPL(2) S D TYPE(4) https://wiki.osdev.org/Interrupt_Descriptor_Table#Structure_IA-32
	unsigned short offset_high;
}__attribute__((packed));

struct idt_ptr
{
	unsigned short size;
	struct idt_entry* ptr;
}__attribute__((packed));

void load_idt(struct idt_ptr idt);

struct cpu_state {
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
	unsigned int edi;
	unsigned int esi;
	unsigned int ebp;
	unsigned int esp;
}__attribute__((packed));

struct stack_state {
	unsigned int error_code;
	unsigned int eip;
	unsigned int cs;
	unsigned int eflags;
}__attribute__((packed));

// CPU Exceptions
void interrupt_handler_0();
void interrupt_handler_1();
void interrupt_handler_2();
void interrupt_handler_3();
void interrupt_handler_4();
void interrupt_handler_5();
void interrupt_handler_6();
void interrupt_handler_7();
void interrupt_handler_8();
// 9 outdated
void interrupt_handler_10();
void interrupt_handler_11();
void interrupt_handler_12();
void interrupt_handler_13();
void interrupt_handler_14();
// 15 reserved
void interrupt_handler_16();
void interrupt_handler_17();
void interrupt_handler_18();
void interrupt_handler_19();
void interrupt_handler_20();
// 21-29 reserved
void interrupt_handler_30();
// 31 reserved

// PIC Interrupts
void interrupt_handler_33(); // Keyboard

#endif
