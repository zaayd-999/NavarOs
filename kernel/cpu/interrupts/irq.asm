[BITS 32]

global irq0
global irq1

extern irq_handler

irq0:
    pusha
    push dword 0
    call irq_handler
    add esp, 4
    popa
    iretd

irq1:
    pusha
    push dword 1
    call irq_handler
    add esp, 4
    popa
    iretd