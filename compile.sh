#! /bin/bash

sed -i 's/\r//' compile.sh

mkdir -p output

# Assembly
nasm cpu/isr.asm -f elf32 -o output/isr.o
nasm cpu/irq.asm -f elf32 -o output/irq_asm.o

# Bootloader
nasm boot/bootloader.asm -f bin -o output/bootloader.bin
nasm boot/kernel_entry.asm -f elf32 -o output/kernel_entry.o

# Drivers
g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c drivers/vga/vga.cpp -o output/vga.o

g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c drivers/keyboard/keyboard.cpp -o output/keyboard.o

# CPU
g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c cpu/idt.cpp -o output/idt.o

g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c cpu/irq.cpp -o output/irq_cpp.o

g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c cpu/pic.cpp -o output/pic.o

# Shell
g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c shell/shell.cpp -o output/shell.o

g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c shell/line_editor.cpp -o output/line_editor.o

g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -fno-pie -fno-pic \
    -nostdlib -nodefaultlibs \
    -c shell/history.cpp -o output/history.o
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
    output/history.o

# Extract raw binary
objcopy -O binary output/kernel.elf output/kernel.bin

# Combine bootloader + kernel
cat output/bootloader.bin output/kernel.bin > output/os.bin

echo "Done! output/os.bin is ready"