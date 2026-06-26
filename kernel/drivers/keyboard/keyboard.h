#ifndef KEYBOARD_H
#define KEYBOARD_H

struct keyInfo {
    char normal;
    char shifted;
    char ctrl;
    char alt;
};

enum keyboardLayout {
    KEYBOARD_LAYOUT_US,
    KEYBOARD_LAYOUT_FR
};

void set_keyboard_layout(keyboardLayout layout);
void set_keyboard_layout();
keyboardLayout get_keyboard_layout();

void keyboard_init();
void keyboard_handler();

#endif