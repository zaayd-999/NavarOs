#ifndef KEYBOARD_H
#define KEYBOARD_H

struct keyInfo {
    char normal;
    char shifted;
    char ctrl;
    char alt;
};

void keyboard_init();
void keyboard_handler();


#endif