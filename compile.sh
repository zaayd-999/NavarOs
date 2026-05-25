#! /bin/bash

sed -i 's/\r//' compile.sh

# create output folder if not exists
mkdir -p output

# bootloader
nasm boot/bootloader.asm -f bin -o output/bootloader.bin
nasm boot/kernel_entry.asm -f elf32 -o output/kernel_entry.o

# drivers
g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -nostdlib -nodefaultlibs \
    -c drivers/vga/vga.cpp -o output/vga.o

# kernel
g++ -m32 -ffreestanding -fno-exceptions -fno-rtti \
    -fno-builtin -fno-stack-protector \
    -nostdlib -nodefaultlibs \
    -c kernel/kernel.cpp -o output/kernel.o

# link
ld -m elf_i386 -T link.ld \
    -o output/kernel.elf \
    output/kernel_entry.o \
    output/vga.o \
    output/kernel.o

# extract raw binary
objcopy -O binary output/kernel.elf output/kernel.bin

# combine
cat output/bootloader.bin output/kernel.bin > output/os.bin

echo "Done! output/os.bin is ready"