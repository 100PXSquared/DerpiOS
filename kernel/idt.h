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

void interrupt_handler(struct cpu_state cpu, struct stack_state stack, unsigned int interrupt);

void interrupt_handler_0();

#endif