#include <stdint.h>
#include "gdt.h"

struct gdt_pointer {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed));

static uint64_t gdt[] = {
    0x0000000000000000, // 0x00: Null descriptor
    0x00AF9A000000FFFF, // 0x08: Kernel code
    0x00CF92000000FFFF  // 0x10: Kernel data
};

extern void gdt_load(const struct gdt_pointer *ptr);

void gdt_init(void) {
    struct gdt_pointer ptr = {
        .limit = sizeof(gdt) - 1,
        .base = (uint64_t)gdt
    };

    gdt_load(&ptr);
}