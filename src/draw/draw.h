
#ifndef DRAW_H
#define DRAW_H

#include <limine.h>

void draw_init(struct limine_framebuffer *_fb);
void draw_pixel(int x, int y, int color);
void clear_screen();
void draw_cursor(int x, int y);

#endif