#include "shell.h"
#include "../drivers/vga/vga.h"
#include "line_editor.h"
#include "history.h"
#include "../drivers/keyboard/keyboard.h"
#include "command_parser.h"

static bool equals(const char* a, const char* b) {
    int i = 0;
    while(a[i] && b[i]) {
        if(a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

static keyboardLayout keyboard_layout_from_string(const char* lang) {
    if(equals(lang,"us")) return KEYBOARD_LAYOUT_US;
    if(equals(lang,"fr")) return KEYBOARD_LAYOUT_FR;
    return KEYBOARD_LAYOUT_US;
}

void shell_print_prompt() {
    print_string("> ");
    line_editor_init();

}

void shell_init() {
    set_color(WHITE,BLACK);
    print_string("NavarOs Shell V1.0.0");
    new_line();
    history_init();
    shell_print_prompt();
}

/*
void shell_execute_cmd(const char* command) {
    Command cmd = parse_command(command);
    if(equals(cmd.,"!")) {
        const char* last = history_top();
        if(last==nullptr) {
            print_string("No commands in history.");
            new_line();
            shell_print_prompt();
            return;
        }

        print_string(last);
        new_line();
        shell_execute_cmd(last);
        return;
    }

    history_add(cmd);

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

    if(equals(cmd,"exit")) {
        print_string("Exiting NavarOs shell....");
        new_line();
        while(1){
            asm volatile("hlt");
        }
    }

    if(equals(cmd, "layout us")) {
        set_keyboard_layout(KEYBOARD_LAYOUT_US);
        print_string("Keyboard layout: US");
        new_line();
        shell_print_prompt();
        return;
    }

    if(equals(cmd,"layout fr")) {
        set_keyboard_layout(KEYBOARD_LAYOUT_FR);
        print_string("Keyboard layout: FR");
        new_line();
        shell_print_prompt();
        return;
    }
    
    print_string("Unknown command: ");
    print_string(cmd);
    new_line();
    shell_print_prompt();
}

*/

void shell_execute_cmd(const char* input) {
    Command cmd = parse_command(input);
    const char* cmd_name = cmd.name;

    if(cmd_name == nullptr) {
        shell_print_prompt();
        return;
    }

    if(equals(cmd_name,"!")) {
        const char* last = history_top();
        if(last==nullptr) {
            print_string("No commands in history.");
            new_line();
            shell_print_prompt();
            return;
        }

        print_string(last);
        new_line();
        shell_execute_cmd(last);
        return;
    }

    history_add(input);

    if(equals(cmd_name,"clear")) {
        clear_screen();
        shell_print_prompt();
        return;
    }

    if(equals(cmd_name,"help")) {
        print_string("Commands: clear, help, exit, layout, version");
        new_line();
        shell_print_prompt();
        return;
    }

    if(equals(cmd_name,"exit")) {
        print_string("Exiting NavarOs shell....");
        new_line();
        while(1){
            asm volatile("hlt");
        }
    }

    if(equals(cmd_name, "version")) {
        print_string("NavarOs v1.0.0");
        new_line();
        shell_print_prompt();
        return;
    }

    if(equals(cmd_name, "layout")) {
        if(cmd.argc == 0) {
            print_string("Usage: layout us|fr");
            new_line();
            shell_print_prompt();
            return;
        }

        const char* lang = cmd.args[0];

        keyboardLayout layout = keyboard_layout_from_string(lang);
        
        set_keyboard_layout(layout);

        print_string("keyboard layout changed.");
        new_line();
        shell_print_prompt();
        return;
        
    }

    if(equals(cmd_name, "color")) {
        set_color(CYAN,BLACK);
        new_line();
        shell_print_prompt();
        return;
    }

    if(equals(cmd_name,"echo")) {
        if(cmd.argc == 0) {
            unsigned char color_used = get_color();
            set_color(YELLOW,BLACK);
            print_string("Syntax: echo text [FLAGS]");
            set_color(color_used);
            new_line();
            shell_print_prompt();
            return;
        }
        const char* text = cmd.args[0];
        print_string(text);
        new_line();
        shell_print_prompt();
        return;
    }
    
    print_string("Unknown command: ");
    print_string(input);
    new_line();
    shell_print_prompt();
}