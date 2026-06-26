#ifndef LINE_EDITOR_H
#define LINE_EDITOR_H

void line_editor_init();
void line_editor_insert_char(char c);
void line_editor_backspace();
void line_editor_move_left();
void line_editor_move_right();
const char* line_editor_get_buffer();
void line_editor_clear();
void line_editor_set_text(const char* text);

#endif