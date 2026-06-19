#include "keyboard.h"
#include "../../cpu/ports.h"
#include "../vga/vga.h"
#include "keyboard.h"
#include "../../shell/shell.h"

static keyInfo keymap[128];
static bool shift_pressed = false;
static bool ctr_pressed = false;
static bool alt_pressed = false;
static bool caps_pressed = false;

void keyboard_init() {
    
    keymap[0x02] = {'1', '!'};
    keymap[0x03] = {'2', '@'};
    keymap[0x04] = {'3', '#'};
    keymap[0x05] = {'4', '$'};
    keymap[0x06] = {'5', '%'};
    keymap[0x07] = {'6', '^'};
    keymap[0x08] = {'7', '&'};
    keymap[0x09] = {'8', '*'};
    keymap[0x0A] = {'9', '('};
    keymap[0x0B] = {'0', ')'};

    keymap[0x10] = {'q', 'Q'};
    keymap[0x11] = {'w', 'W'};
    keymap[0x12] = {'e', 'E'};
    keymap[0x13] = {'r', 'R'};
    keymap[0x14] = {'t', 'T'};
    keymap[0x15] = {'y', 'Y'};
    keymap[0x16] = {'u', 'U'};
    keymap[0x17] = {'i', 'I'};
    keymap[0x18] = {'o', 'O'};
    keymap[0x19] = {'p', 'P'};

    keymap[0x1E] = {'a', 'A'};
    keymap[0x1F] = {'s', 'S'};
    keymap[0x20] = {'d', 'D'};
    keymap[0x21] = {'f', 'F'};
    keymap[0x22] = {'g', 'G'};
    keymap[0x23] = {'h', 'H'};
    keymap[0x24] = {'j', 'J'};
    keymap[0x25] = {'k', 'K'};
    keymap[0x26] = {'l', 'L'};

    keymap[0x2C] = {'z', 'Z'};
    keymap[0x2D] = {'x', 'X'};
    keymap[0x2E] = {'c', 'C'};
    keymap[0x2F] = {'v', 'V'};
    keymap[0x30] = {'b', 'B'};
    keymap[0x31] = {'n', 'N'};
    keymap[0x32] = {'m', 'M'};

    keymap[0x39] = {' ', ' '};   // Space
    keymap[0x1C] = {'\n', '\n'}; // Enter
    //keymap[0x0E] = {'\b', '\b'}; // Backspace

}


static char input_buffer[256];
static int input_length = 0;

void keyboard_handler() {
    unsigned char scancode = inb(0x60);
	
	if(scancode == 0x3A) caps_pressed = !caps_pressed; // Toggle Caps lock
    
	if(scancode == 0x2A || scancode == 0x36) {
        shift_pressed = true;
        return;
    }

     if (scancode == 0xAA || scancode == 0xB6) { // Release = Press + 0x80
        shift_pressed = false;
        return;
    }
	
	bool uppercase = shift_pressed ^ caps_pressed; // Shift XOR Caps

    if(scancode & 0x80) {
        return;
    }

    if(scancode >= 128) return;

    if(scancode == 0x1C && !shift_pressed) {
        new_line();
        shell_execute_cmd(input_buffer);
        input_buffer[0] = '\0';
        input_length = 0;
        return;
    }

    // Next Implementing the delete

    char c = uppercase ? keymap[scancode].shifted : keymap[scancode].normal;

    if(c) {
        print_char(c);
        input_buffer[input_length] = c;
        input_length++;
        input_buffer[input_length] = '\0';
    }

}