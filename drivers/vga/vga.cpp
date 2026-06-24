#include "vga.h"
#include "../../cpu/ports.h"
#include "../../constants.h"

unsigned short* vga    = (unsigned short*)0xB8000;
unsigned char cursor_row = 0;
unsigned char cursor_col = 0;
unsigned char color      = 0x0F;

void set_color(unsigned char fg, unsigned char bg) {
    color = (bg << 4) | fg;
}

void set_color(unsigned char colour) {
    color = colour;
}


unsigned char get_color_at(unsigned char row, unsigned char col) {
    return (vga[row * VGA_WIDTH + col] >> 8 ) & 0xFF;
}

void clear_screen() {
    for (int i = 0; i < 80 * 25; i++) {
        vga[i] = (color << 8) | ' ';
    }
    cursor_row = 0;
    cursor_col = 0;
}

void new_line() {
    cursor_col = 0;
    cursor_row++;
    if (cursor_row >= 25) {
        for (int i = 0; i < 80 * 24; i++) {
            vga[i] = vga[i + 80];
        }
        for (int i = 80 * 24; i < 80 * 25; i++) {
            vga[i] = (color << 8) | ' ';
        }
        cursor_row = 24;
    }
}

void print_char(char c) {
    if (c == '\n') {
        new_line();
        return;
    }
    int index = cursor_row * 80 + cursor_col;
    vga[index] = (color << 8) | c;
    cursor_col++;
    if (cursor_col >= 80) {
        new_line();
    }
    move_cursor();
}

void print_string(const char* str) {
    for (int i = 0; str[i] != 0; i++) {
        print_char(str[i]);
    }
}

void print_int(int n) {
    if (n < 0) {
        print_char('-');
        n = -n;
    }

    if (n == 0) {
        print_char('0');
        return;
    }

    char buf[32];
    int i = 0;

    while (n > 0) {
        buf[i++] = '0' + (n % 10);
        n /= 10;
    }

    // reverse
    for (int j = i - 1; j >= 0; j--) {
        print_char(buf[j]);
    }
}

void print_hex(unsigned int n) {
    print_string("0x");

    char hex[] = "0123456789ABCDEF";
    char buf[8];

    for (int i = 7; i >= 0; i--) {
        buf[i] = hex[n & 0xF];
        n >>= 4;
    }

    bool leading = true;
    for (int i = 0; i < 8; i++) {
        if (buf[i] != '0') leading = false;
        if (!leading) print_char(buf[i]);
    }

    if (leading) print_char('0');
}

void hide_cursor() {
    asm volatile (
        "movw $0x3D4, %dx\n"
        "movb $0x0A, %al\n"
        "outb %al, %dx\n"
        "movw $0x3D5, %dx\n"
        "movb $0x20, %al\n"
        "outb %al, %dx\n"
    );
}

void move_cursor() {
    unsigned short pos = cursor_row * 80 + cursor_col;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(pos & 0xFF));

    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char)((pos>>8) & 0xFF));
}

void backspace() {
    if(cursor_row == 0 && cursor_col == 0) return;

    if(cursor_col > 0) {
        cursor_col--;
    } else {
        cursor_row--;
        cursor_col = 79;
    }

    int index = cursor_row * 80 + cursor_col;
    vga[index] = (color << 8) | ' ';
}

void set_cursor_style_bar() {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x00);

    outb(0x3D4, 0x0B);
    outb(0x3D5, 0x0F);
}

unsigned char get_color() {
    return color;
}