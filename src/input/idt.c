#include <stdint.h>
#include <stddef.h>
#include "idt.h"
#include "text/text.h"
#include "text/colors.h"

struct idt_entry {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t  ist;
    uint8_t  attributes;
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t reserved;
} __attribute__((packed));

struct idt_pointer {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

static struct idt_entry idt[256];

extern void *isr_stub_table[];

__attribute__((noreturn))
void exception_handler(uint64_t vector, uint64_t error_code) {
    (void)error_code;

    println("!!! CPU EXCEPTION !!!", WHITE);
    println("TelpOS kernel halted.", WHITE);

    (void)vector;

    for (;;) {
        __asm__ volatile ("cli; hlt");
    }
}

static void idt_set_gate(uint8_t vector, uintptr_t handler) {
    idt[vector].offset_low  = handler & 0xFFFF;
    idt[vector].selector    = 0x08;
    idt[vector].ist         = 0;
    idt[vector].attributes  = 0x8E;
    idt[vector].offset_mid  = (handler >> 16) & 0xFFFF;
    idt[vector].offset_high = (handler >> 32) & 0xFFFFFFFF;
    idt[vector].reserved    = 0;
}

void idt_init(void) {
    for (uint8_t i = 0; i < 32; i++) {
        idt_set_gate(i, (uintptr_t)isr_stub_table[i]);
    }

    struct idt_pointer ptr = {
        .limit = sizeof(idt) - 1,
        .base  = (uintptr_t)idt
    };

    __asm__ volatile ("lidt %0" : : "m"(ptr) : "memory");
}