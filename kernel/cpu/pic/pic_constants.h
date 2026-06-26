#pragma once

constexpr unsigned char PIC1         = 0x20;
constexpr unsigned char PIC2         = 0xA0;

constexpr unsigned char PIC1_COMMAND = PIC1;
constexpr unsigned char PIC1_DATA    = PIC1+1;
constexpr unsigned char PIC2_COMMAND = PIC2;
constexpr unsigned char PIC2_DATA    = PIC2+1;

constexpr unsigned char PIC_EOI      = 0x20;
