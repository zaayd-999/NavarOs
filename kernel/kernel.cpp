#include "../drivers/vga/vga.h"
#include "../cpu/idt.h"
#include "../cpu/irq.h"
#include "../drivers/keyboard/keyboard.h"

extern "C" void kernel_main() {
    clear_screen();
    hide_cursor();

    print_string("NavarOs is ");
    set_color(GREEN, BLACK);
    print_string("OK");
    set_color(WHITE, BLACK);
    print_string("!");
    new_line();

    print_string("Loading IDT...");
    new_line();

    idt_init();

    print_string("IDT loaded successfully.");
    new_line();

    print_string("Testing Keyboard.");
    new_line();

    keyboard_init();

    asm volatile("sti");

    while (1);
}