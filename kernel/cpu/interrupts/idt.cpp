#include "idt.h"
#include "irq.h"
#include "../pic/pic.h"
#include "../../drivers/vga/vga.h"
#include "../../drivers/keyboard/keyboard.h"
#include "idt_constants.h"

IDTEntry idt[IDT_ENTIES];
IDTPointer idt_ptr;

static void idt_set_gate(int n , unsigned int handler) {
    idt[n].base_low = handler & 0xFFFF;
    idt[n].selector = 0x08;
    idt[n].zero = 0;
    idt[n].flags = 0x8E;
    idt[n].base_high = (handler >> 16) & 0xFFFF;
};

extern "C" void idt_load(unsigned int);

void idt_init() {

    pic_remap();

    idt_ptr.limit = sizeof(IDTEntry) * IDT_ENTIES - 1;
    idt_ptr.base = (unsigned int)&idt;
    
    for (int i = 0 ; i < IDT_ENTIES; i++) {
        idt_set_gate(i, 0);
    }

    idt_set_gate(0, (unsigned) isr0);
    idt_set_gate(6,  (unsigned int)isr6);
    idt_set_gate(13, (unsigned int)isr13);
    idt_set_gate(14, (unsigned int)isr14);
    idt_set_gate(32, (unsigned int)irq0);
    idt_set_gate(33, (unsigned int)irq1);
    idt_load((unsigned int)&idt_ptr);
}

extern "C" void isr_handler(int interrupt_number) {
    set_color(RED, BLACK);

    print_string("CPU Exception: ");

    if (interrupt_number == 0)
        print_string("Divide by zero");
    else if (interrupt_number == 6)
        print_string("Invalid opcode");
    else if (interrupt_number == 13)
        print_string("General protection fault");
    else if (interrupt_number == 14)
        print_string("Page fault");
    else
        print_string("Unknown interrupt");

    new_line();

    set_color(WHITE, BLACK);

    while (1);
}