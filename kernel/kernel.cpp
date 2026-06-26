#include "./drivers/vga/vga.h"
#include "./cpu/interrupts/idt.h"
#include "./cpu/interrupts/irq.h"
#include "./drivers/keyboard/keyboard.h"
#include "./shell/editor/shell.h"

extern "C" void kernel_main() {
    clear_screen();
    //hide_cursor();
    set_cursor_style_bar();
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

    shell_init();

    keyboard_init();

    asm volatile("sti");

    while (1);
}