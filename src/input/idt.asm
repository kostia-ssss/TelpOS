bits 64
default rel

section .text

extern exception_handler
global isr_stub_table

%macro ISR_NO_ERROR 1
isr%1:
    mov edi, %1
    xor esi, esi
    and rsp, -16
    call exception_handler
.hang%1:
    cli
    hlt
    jmp .hang%1
%endmacro

%macro ISR_ERROR 1
isr%1:
    mov edi, %1
    mov esi, [rsp]
    and rsp, -16
    call exception_handler
.hang%1:
    cli
    hlt
    jmp .hang%1
%endmacro

ISR_NO_ERROR 0
ISR_NO_ERROR 1
ISR_NO_ERROR 2
ISR_NO_ERROR 3
ISR_NO_ERROR 4
ISR_NO_ERROR 5
ISR_NO_ERROR 6
ISR_NO_ERROR 7
ISR_ERROR     8
ISR_NO_ERROR 9
ISR_ERROR    10
ISR_ERROR    11
ISR_ERROR    12
ISR_ERROR    13
ISR_ERROR    14
ISR_NO_ERROR 15
ISR_NO_ERROR 16
ISR_ERROR    17
ISR_NO_ERROR 18
ISR_NO_ERROR 19
ISR_NO_ERROR 20
ISR_ERROR    21
ISR_NO_ERROR 22
ISR_NO_ERROR 23
ISR_NO_ERROR 24
ISR_NO_ERROR 25
ISR_NO_ERROR 26
ISR_NO_ERROR 27
ISR_NO_ERROR 28
ISR_ERROR    29
ISR_ERROR    30
ISR_NO_ERROR 31

section .rodata
align 8

isr_stub_table:
%assign i 0
%rep 32
    dq isr%+i
%assign i i+1
%endrep