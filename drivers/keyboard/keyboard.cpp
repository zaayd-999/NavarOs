#include "keyboard.h"
#include "../../cpu/ports.h"
#include "../vga/vga.h"
#include "keyboard.h"
#include "../../shell/shell.h"
#include "../../shell/line_editor.h"
#include "../../shell/history.h"

static keyInfo keymap_us[128];
static keyInfo keymap_fr[128];
static keyInfo keymap_ar[128];
static bool shift_pressed = false;
static bool ctr_pressed = false;
static bool alt_pressed = false;
static bool caps_pressed = false;
static bool extended_keys = false;
static keyboardLayout current_layout = KEYBOARD_LAYOUT_US;

void set_keyboard_layout(keyboardLayout layout) {
    current_layout = layout;
}

void set_keyboard_layout() {
    set_keyboard_layout(KEYBOARD_LAYOUT_US);
}

void keyboard_init() {
    
    keymap_us[0x02] = {'1', '!'};
    keymap_us[0x03] = {'2', '@'};
    keymap_us[0x04] = {'3', '#'};
    keymap_us[0x05] = {'4', '$'};
    keymap_us[0x06] = {'5', '%'};
    keymap_us[0x07] = {'6', '^'};
    keymap_us[0x08] = {'7', '&'};
    keymap_us[0x09] = {'8', '*'};
    keymap_us[0x0A] = {'9', '('};
    keymap_us[0x0B] = {'0', ')'};

    keymap_us[0x10] = {'q', 'Q'};
    keymap_us[0x11] = {'w', 'W'};
    keymap_us[0x12] = {'e', 'E'};
    keymap_us[0x13] = {'r', 'R'};
    keymap_us[0x14] = {'t', 'T'};
    keymap_us[0x15] = {'y', 'Y'};
    keymap_us[0x16] = {'u', 'U'};
    keymap_us[0x17] = {'i', 'I'};
    keymap_us[0x18] = {'o', 'O'};
    keymap_us[0x19] = {'p', 'P'};

    keymap_us[0x1E] = {'a', 'A'};
    keymap_us[0x1F] = {'s', 'S'};
    keymap_us[0x20] = {'d', 'D'};
    keymap_us[0x21] = {'f', 'F'};
    keymap_us[0x22] = {'g', 'G'};
    keymap_us[0x23] = {'h', 'H'};
    keymap_us[0x24] = {'j', 'J'};
    keymap_us[0x25] = {'k', 'K'};
    keymap_us[0x26] = {'l', 'L'};

    keymap_us[0x2C] = {'z', 'Z'};
    keymap_us[0x2D] = {'x', 'X'};
    keymap_us[0x2E] = {'c', 'C'};
    keymap_us[0x2F] = {'v', 'V'};
    keymap_us[0x30] = {'b', 'B'};
    keymap_us[0x31] = {'n', 'N'};
    keymap_us[0x32] = {'m', 'M'};

    keymap_us[0x39] = {' ', ' '};   // Space
    keymap_us[0x1C] = {'\n', '\n'}; // Enter
    //keymap_us[0x0E] = {'\b', '\b'}; // Backspace
    
    keymap_fr[0x02] = {'&', '1'};
    keymap_fr[0x03] = {'e', '2'};
    keymap_fr[0x04] = {'"', '3'};
    keymap_fr[0x05] = {'\'', '4'};
    keymap_fr[0x06] = {'(', '5'};
    keymap_fr[0x07] = {'-', '6'};
    keymap_fr[0x08] = {'e', '7'};  // è
    keymap_fr[0x09] = {'_', '8'};
    keymap_fr[0x0A] = {'c', '9'};  // ç
    keymap_fr[0x0B] = {'a', '0'};  // à

    keymap_fr[0x10] = {'a', 'A'};
    keymap_fr[0x11] = {'z', 'Z'};
    keymap_fr[0x12] = {'e', 'E'};
    keymap_fr[0x13] = {'r', 'R'};
    keymap_fr[0x14] = {'t', 'T'};
    keymap_fr[0x15] = {'y', 'Y'};
    keymap_fr[0x16] = {'u', 'U'};
    keymap_fr[0x17] = {'i', 'I'};
    keymap_fr[0x18] = {'o', 'O'};
    keymap_fr[0x19] = {'p', 'P'};

    keymap_fr[0x1E] = {'q', 'Q'};
    keymap_fr[0x1F] = {'s', 'S'};
    keymap_fr[0x20] = {'d', 'D'};
    keymap_fr[0x21] = {'f', 'F'};
    keymap_fr[0x22] = {'g', 'G'};
    keymap_fr[0x23] = {'h', 'H'};
    keymap_fr[0x24] = {'j', 'J'};
    keymap_fr[0x25] = {'k', 'K'};
    keymap_fr[0x26] = {'l', 'L'};

    keymap_fr[0x2C] = {'w', 'W'};
    keymap_fr[0x2D] = {'x', 'X'};
    keymap_fr[0x2E] = {'c', 'C'};
    keymap_fr[0x2F] = {'v', 'V'};
    keymap_fr[0x30] = {'b', 'B'};
    keymap_fr[0x31] = {'n', 'N'};
    keymap_fr[0x32] = {',', '?'};

    keymap_fr[0x39] = {' ', ' '};
    keymap_fr[0x1C] = {'\n', '\n'};

    set_keyboard_layout();

}


keyboardLayout get_keyboard_layout() {
    return current_layout;
}

void keyboard_handler() {
    unsigned char scancode = inb(0x60);
	
    if(scancode == 0xE0) {
        extended_keys = true;
        return;
    }

    if(extended_keys) {
        extended_keys = false;
        if(scancode == 0x4B) {
            line_editor_move_left();
            return;
        }

        if(scancode == 0x4D) {
            line_editor_move_right();
            return;
        }

        if(scancode == 0x48) {
            const char* cmd = history_previous();
            if(cmd) line_editor_set_text(cmd);
            return;
        }

        if(scancode == 0x50) {
            const char* cmd = history_next();
            if(cmd) line_editor_set_text(cmd);
            return;
        }

        return;
    }

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
        
        const char* cmd = line_editor_get_buffer();
        
        shell_execute_cmd(cmd);

        line_editor_clear();

        return;
    }

    if(scancode == 0x0E) {
        line_editor_backspace();    
        return;
    }

    keyInfo* keymap = current_layout == 1 ? keymap_fr : keymap_us;
    char c = uppercase ? keymap[scancode].shifted : keymap[scancode].normal;

    if(c) {
        line_editor_insert_char(c);    
        return;
    }

}
