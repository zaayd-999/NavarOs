#ifndef IDT_H
#define IDT_H

struct IDTEntry {
    unsigned short base_low;
    unsigned short selector;
    unsigned char zero;
    unsigned char flags;
    unsigned short base_high;
} __attribute__((packed));

struct IDTPointer {
    unsigned short limit;
    unsigned int base;
} __attribute__ ((packed));

void idt_init();

extern "C" void isr0();
extern "C" void isr6();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void idt_load(unsigned int);
extern "C" void isr_handler(int interrupt_number);

#endif