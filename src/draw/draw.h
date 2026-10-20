
#ifndef DRAW_H
#define DRAW_H

#include <limine.h>

void draw_init(struct limine_framebuffer *_fb);
void draw_pixel(int x, int y, int color);
void clear_screen();
void draw_cursor(int x, int y);
void draw_rect(int x, int y, int w, int h, int color);

#endif