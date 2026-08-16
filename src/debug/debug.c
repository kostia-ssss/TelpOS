#include "../debug/debug.h"

void debug(struct limine_framebuffer *fb,
           uint32_t color,
           char *caption,
           char *message)
{
    print_color(fb, "[", color);
    print_color(fb, caption, color);
    print_color(fb, "] ", color);
    println_color(fb, message, color);
}