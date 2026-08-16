#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <stdint.h>
#include <stddef.h>
#include "../boot/limine.h"

void put_pixel(struct limine_framebuffer *fb,
            size_t x,
            size_t y,
            uint32_t color);

void draw_rect(struct limine_framebuffer *fb,
            size_t x,
            size_t y,
            size_t w,
            size_t h,
            uint32_t color);

void draw_char(struct limine_framebuffer *fb,
            size_t letter_x,
            size_t letter_y,
            size_t size,
            uint32_t color,
            char c);

void draw_string(struct limine_framebuffer *fb,
            size_t x,
            size_t y,
            uint32_t color,
            size_t letter_size,
            char* text);

#endif