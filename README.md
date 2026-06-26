# 🚀 NavarOS

> A 32-bit x86 operating system built from scratch using **C++** and **x86 Assembly**.

![Status](https://img.shields.io/badge/status-active%20development-yellow)
![Architecture](https://img.shields.io/badge/architecture-x86%2032--bit-green)
![Language](https://img.shields.io/badge/language-C%2B%2B%20%7C%20Assembly-blue)
![License](https://img.shields.io/badge/license-MIT-lightgrey)

---

## 📖 About

NavarOS is a personal operating system project created to learn low-level systems programming by implementing every major operating system component from scratch.

The project starts from a custom BIOS bootloader and gradually builds a complete operating system including interrupt handling, device drivers, memory management, a shell, a file system, and eventually multitasking.

---

# ✨ Current Features

## Boot Process

* ✅ Custom 512-byte bootloader
* ✅ Loads kernel from disk
* ✅ Switches from Real Mode to Protected Mode
* ✅ Global Descriptor Table (GDT)

---

## Kernel

* ✅ 32-bit C++ kernel
* ✅ Custom linker script
* ✅ Stack initialization
* ✅ Modular architecture

---

## VGA Driver

* ✅ print_char()
* ✅ print_string()
* ✅ print_int()
* ✅ print_hex()
* ✅ clear_screen()
* ✅ scroll()
* ✅ new_line()
* ✅ set_color()
* ✅ Hardware cursor
* ✅ Cursor movement
* ✅ Cursor visibility

---

## Interrupt Management

* ✅ Interrupt Descriptor Table (IDT)
* ✅ Interrupt Service Routines (ISR)
* ✅ PIC Remapping
* ✅ CPU Exception Handling

---

## Keyboard Driver

* ✅ PS/2 Keyboard Driver
* ✅ Scancode Set 1
* ✅ Shift Support
* ✅ Multiple Keyboard Layouts
* ✅ Runtime Layout Switching

---

## Interactive Shell

* ✅ Command execution
* ✅ Interactive line editor
* ✅ Left / Right cursor movement
* ✅ Character insertion
* ✅ Backspace
* ✅ Command history
* ✅ Execute previous command (`!`)

---

## Command Parser

Supports commands such as:

```text
create user --name "Zaayd Kaiche" --password "my \"secret\"" --admin
```

Features:

* ✅ Positional arguments
* ✅ Boolean flags
* ✅ String flags
* ✅ Long options (`--name`)
* ✅ Quoted strings
* ✅ Escape sequences

---

# 📁 Project Structure

```text
NavarOS
│
├── boot/
│   ├── bootloader.asm
│   └── kernel_entry.asm
│
├── kernel/
│   ├── kernel.cpp
│   ├── cpu/
│   │     ├── interrupts/
│   │     ├── pic/
│   │     └── ports/
│   │
│   ├── drivers/
│   │     ├── keyboard/
│   │     └── vga/
│   │
│   └── shell/
│         ├── editor/
│         └── parser/
│
├── output/
├── compile.sh
├── run.sh
└── README.md
```

---

# 🖥️ Build

## Arch Linux

```bash
sudo pacman -S \
nasm \
gcc \
binutils \
qemu-system-x86
```

## Ubuntu

```bash
sudo apt install \
nasm \
gcc \
g++ \
gcc-multilib \
g++-multilib \
binutils \
qemu-system-x86
```

Build:

```bash
bash compile.sh
```

Run:

```bash
bash run.sh
```

---

# 🧠 Boot Sequence

```text
BIOS
   │
   ▼
Bootloader
   │
   ▼
Real Mode
   │
   ▼
Protected Mode
   │
   ▼
Kernel Entry
   │
   ▼
Kernel Initialization
   │
   ├── GDT
   ├── IDT
   ├── ISR
   ├── IRQ
   ├── VGA
   ├── Keyboard
   └── Shell
```

---

# 🗺️ Roadmap

## Completed

* ✅ Bootloader
* ✅ Protected Mode
* ✅ GDT
* ✅ VGA Driver
* ✅ IDT
* ✅ ISR
* ✅ IRQ
* ✅ Keyboard Driver
* ✅ Interactive Shell
* ✅ Command History
* ✅ Line Editor
* ✅ Command Parser

## In Progress

* 🚧 Paging
* 🚧 Physical Memory Manager

## Planned

* ⬜ Heap (`kmalloc`)
* ⬜ ATA Driver
* ⬜ File System
* ⬜ ELF Loader
* ⬜ User Mode
* ⬜ Scheduler
* ⬜ Multitasking
* ⬜ Virtual File System
* ⬜ Mouse Driver
* ⬜ PCI
* ⬜ Networking
* ⬜ Graphical Interface

---

# 📷 Screenshots

[ NavarOS Development Log #1 | Interactive Shell & Advanced Command Parser ](https://youtu.be/blMKrGNLY0g)

---

# 🎯 Goal

The objective of NavarOS is not simply to create another operating system, but to understand how every major subsystem works by implementing it from scratch—from the bootloader to multitasking.

---

# 📄 License

MIT License
