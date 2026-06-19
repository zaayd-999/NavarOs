#include "shell.h"
#include "../drivers/vga/vga.h"

static bool equals(const char* a, const char* b) {
    int i = 0;
    while(a[i] && b[i]) {
        if(a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

void shell_print_prompt() {
    print_string("> ");
}

void shell_init() {
    set_color(WHITE,BLACK);
    print_string("NavarOs Shell V1.0.0");
    new_line();
    shell_print_prompt();
}

void shell_execute_cmd(const char* cmd) {
    if(equals(cmd,"clear")) {
        clear_screen();
        shell_print_prompt();
        return;
    }

    if(equals(cmd,"help")) {
        print_string("Commands: clear, help");
        new_line();
        shell_print_prompt();
        return;
    }

    print_string("Unknown command: ");
    print_string(cmd);
    new_line();
    shell_print_prompt();
}