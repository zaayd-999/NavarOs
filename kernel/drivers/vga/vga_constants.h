#pragma once

constexpr unsigned int VGA_MEMORY = (unsigned int) 0xB8000;
constexpr int            VGA_WIDTH  = 80;
constexpr int            VGA_HEIGHT = 25;

extern unsigned short* vga;
extern unsigned char   cursor_row;
extern unsigned char   cursor_col;
extern unsigned char   color;