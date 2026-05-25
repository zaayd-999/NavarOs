#include "../drivers/vga/vga.h"

extern "C" void kernel_main() {
    clear_screen();
    hide_cursor();
    print_string("NavarOs is ");
    set_color(GREEN,BLACK);
    print_string("OK");
    set_color(WHITE,BLACK);
    print_string("!");
    new_line();
    set_color(RED,BLACK);
    print_string("[ X ] ");
    set_color(WHITE,BLACK);
    print_string("zaayd_ka - NavarOs V0.0.1");
    while (1);
}