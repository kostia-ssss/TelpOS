#ifndef TEXT_H
#define TEXT_H

#include <limine.h>

extern const char letters[27][5][6];

const char (*getLetter(char c))[6];

void drawChar(
    struct limine_framebuffer *fb,
    const char (*letter)[6],
    unsigned int x,
    unsigned int y,
    unsigned int color,
    unsigned int scale
);

void drawString(
    struct limine_framebuffer *fb,
    const char* string,
    unsigned int x,
    unsigned int y,
    unsigned int color,
    unsigned int scale
);

#endif