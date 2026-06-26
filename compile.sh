#! /bin/bash

sed -i 's/\r//' compile.sh

mkdir -p output

# Assembly
nasm kernel/cpu/interrupts/isr.asm -f elf32 -o output/isr.o
nasm kernel/cpu/interrupts/irq.asm -f elf32 -o output/irq_asm.o

# Bootloader
nasm boot/bootloader.asm -f bin -o output/bootloader.bin
nasm boot/kernel_entry.asm -f elf32 -o output/kernel_entry.o

# Drivers
g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c kernel/drivers/vga/vga.cpp -o output/vga.o

g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c kernel/drivers/keyboard/keyboard.cpp -o output/keyboard.o

# CPU
g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c kernel/cpu/interrupts/idt.cpp -o output/idt.o

g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c kernel/cpu/interrupts/irq.cpp -o output/irq_cpp.o

g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c kernel/cpu/pic/pic.cpp -o output/pic.o

# Shell
g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c kernel/shell/editor/shell.cpp -o output/shell.o

g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c kernel/shell/editor/line_editor.cpp -o output/line_editor.o

g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c kernel/shell/parser/history.cpp -o output/history.o

g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c kernel/shell/parser/command_parser.cpp -o output/command_parser.o

# Kernel
g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c kernel/kernel.cpp -o output/kernel.o

# Link
ld -m elf_i386 -T link.ld \
    -o output/kernel.elf \
    output/kernel_entry.o \
    output/isr.o \
    output/irq_asm.o \
    output/vga.o \
    output/idt.o \
    output/kernel.o \
    output/pic.o \
    output/irq_cpp.o \
    output/keyboard.o \
    output/shell.o \
    output/line_editor.o \
    output/history.o \
    output/command_parser.o

# Extract raw binary
objcopy -O binary output/kernel.elf output/kernel.bin

# Combine bootloader + kernel
cat output/bootloader.bin output/kernel.bin > output/os.bin

echo "Done! output/os.bin is ready"