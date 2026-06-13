[BITS 32]

global idt_load
global isr0
global isr6
global isr13
global isr14

extern isr_handler

idt_load:
    mov eax, [esp + 4]
    lidt [eax]
    ret

isr0:
    cli
    push dword 0
    call isr_handler
    add esp, 4
    jmp $

isr6:
    cli
    push dword 6
    call isr_handler
    add esp, 4
    jmp $

isr13:
    cli
    add esp, 4
    push dword 13
    call isr_handler
    add esp, 4
    jmp $

isr14:
    cli
    add esp, 4
    push dword 14
    call isr_handler
    add esp, 4
    jmp $