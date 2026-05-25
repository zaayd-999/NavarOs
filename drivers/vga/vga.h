#ifndef VGA_H
#define VGA_H

enum VGA_COLOR {
    BLACK         = 0,
    BLUE          = 1,
    GREEN         = 2,
    CYAN          = 3,
    RED           = 4,
    MAGENTA       = 5,
    BROWN         = 6,
    LIGHT_GRAY    = 7,
    DARK_GRAY     = 8,
    LIGHT_BLUE    = 9,
    LIGHT_GREEN   = 10,
    LIGHT_CYAN    = 11,
    LIGHT_RED     = 12,
    LIGHT_MAGENTA = 13,
    YELLOW        = 14,
    WHITE         = 15
};

void set_color(unsigned char fg, unsigned char bg);
void clear_screen();
void new_line();
void print_char(char c);
void print_string(const char* str);
void print_int(int n);
void print_hex(unsigned int n);
void hide_cursor();
void move_cursor();

#endif