[BITS 16]
[ORG 0x7C00]
start:
    cli
    xor ax, ax
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov sp, 0x7C00

    mov ah, 0x02
    mov al, 64  
    mov ch, 0   
    mov cl, 2   
    mov dh, 0   
    mov dl, 0x80
    mov bx, 0x1000
    int 0x13

    lgdt [gdt_descriptor]
    mov eax, cr0
    or  eax, 1
    mov cr0, eax
    jmp CODE_SEG:protected_mode

; ── GDT ───────────────────────────────────────────────────────────────
gdt_start:
gdt_null:
    dq 0x0000000000000000
gdt_code_desc:
    dw 0xFFFF, 0x0000
    db 0x00, 10011010b, 11001111b, 0x00
gdt_data_desc:
    dw 0xFFFF, 0x0000
    db 0x00, 10010010b, 11001111b, 0x00
gdt_end:

gdt_descriptor:
    dw gdt_end - gdt_start - 1
    dd gdt_start

CODE_SEG equ gdt_code_desc - gdt_start
DATA_SEG equ gdt_data_desc - gdt_start

[BITS 32]
protected_mode:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov esp, 0x90000

    jmp 0x1000 

times 510 - ($ - $$) db 0
dw 0xAA55