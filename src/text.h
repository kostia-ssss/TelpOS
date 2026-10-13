#ifndef TEXT_H
#define TEXT_H

#include <limine.h>

extern const char letters[27][5][6];

const char (*getLetter(char c))[6];

void draw_char_at(
    struct limine_framebuffer *fb,
    const char (*letter)[6],
    unsigned int x,
    unsigned int y,
    unsigned int color
);

void draw_string_at(
    struct limine_framebuffer *fb,
    const char* string,
    unsigned int x,
    unsigned int y,
    unsigned int color
);

void draw_char(
    struct limine_framebuffer *fb,
    const char (*letter)[6],
    unsigned int color
);

void print(
    struct limine_framebuffer *fb,
    const char* string,
    unsigned int color
);

void println(struct limine_framebuffer *fb,
    const char* string,
    unsigned int color
);

#endif