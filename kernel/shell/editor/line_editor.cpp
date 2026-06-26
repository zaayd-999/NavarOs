#include "line_editor.h"
#include "../../drivers/vga/vga.h"
#include "../../drivers/vga/vga_constants.h"

static char buffer[256];
static int length = 0;
static int cursor = 0;

static unsigned char start_row = 0;
static unsigned char start_col = 0;

static void set_cursor_from_input_position() {
    int index = start_row * VGA_WIDTH + start_col + cursor;
    cursor_row = index / VGA_WIDTH;
    cursor_col = index % VGA_WIDTH;

    move_cursor();
}

static void redraw_line() {
    int start_index = start_row * VGA_WIDTH + start_col;

    for(int i = 0 ; i < 265; i++) {
        int index = start_index + i;
        if(index >= VGA_WIDTH*VGA_HEIGHT) break;
        vga[index] = (color<<8) | ' ';
    }

    for(int i = 0; i < length; i++) {
        int index = start_index + i;
        if(index >= VGA_WIDTH * VGA_HEIGHT) break;
        vga[index] = (color<<8) | buffer[i];
    }

    set_cursor_from_input_position();
}

void line_editor_init() {
    length = 0;
    cursor = 0;
    buffer[0] = '\0';

    start_row = cursor_row;
    start_col = cursor_col;
}

void line_editor_insert_char(char c) {
    if(length >= 255) return;

    for(int i = length; i > cursor; i--) {
        buffer[i] = buffer[i-1];
    }

    buffer[cursor] = c;
    length++;
    cursor++;
    buffer[length] = '\0';

    redraw_line();
}

void line_editor_backspace() {
    if(cursor == 0) return;

    for(int i = cursor-1; i < length - 1 ; i++) {
        buffer[i] = buffer[i+1];
    }

    length--;
    cursor--;
    buffer[length] = '\0';

    redraw_line();
}

void line_editor_move_left() {
    if(cursor==0) return;
    cursor--;
    set_cursor_from_input_position();
}

void line_editor_move_right() {
    if(cursor>=length) return;
    cursor++;
    set_cursor_from_input_position();
}

const char* line_editor_get_buffer() {
    return buffer;
}

void line_editor_clear() {
    length = 0;
    cursor = 0;
    buffer[0] = '\0';

    start_row = cursor_row;
    start_col = cursor_col;
}

static void clear_display_line() {
    int start = start_row * VGA_WIDTH + start_col;

    for(int i = 0; i < 256 && start_col + i < VGA_WIDTH ; i++) {
        vga[start+i] = (color<<8) | ' ';
    }
}

void line_editor_set_text(const char* text) {
    clear_display_line();

    length = 0;
    cursor = 0;

    while(text[length] != '\0' && length < 255) {
        buffer[length] = text[length];
        length++;
    }

    buffer[length] = '\0';
    cursor = length;

    redraw_line();
}