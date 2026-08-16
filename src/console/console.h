#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>
#include <stddef.h>
#include "../boot/limine.h"
#include "../graphics/graphics.h"
#include "../graphics/colors.h"
#include <string.h>

void console_init(size_t size, size_t spacing_x, size_t spacing_y);
void println(struct limine_framebuffer *fb, char *text);
void print(struct limine_framebuffer *fb, char *text);
void print_at(struct limine_framebuffer *fb,
              size_t x,
              size_t y,
              char *text);
void console_clear(struct limine_framebuffer *fb);
void putchar(struct limine_framebuffer *fb, char c);
void putchar_color(struct limine_framebuffer *fb, char c, uint32_t color);
void println_color(struct limine_framebuffer *fb, char *text, uint32_t color);
void print_color(struct limine_framebuffer *fb, char *text, uint32_t color);
void delete_previous_char(struct limine_framebuffer *fb);

#endif