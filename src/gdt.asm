bits 64
default rel

section .text
global gdt_load

gdt_load:
    cli
    lgdt [rdi]

    ; Reload CS
    push qword 0x08
    lea rax, [rel .reload_cs]
    push rax
    retfq

.reload_cs:
    ; Reload data segment registers
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ret