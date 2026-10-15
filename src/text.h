#ifndef TEXT_H
#define TEXT_H

#include <limine.h>

extern const char letters[27][5][6];

const char (*getLetter(char c))[6];

void init_text_engine(struct limine_framebuffer *_fb);

void draw_char_at(
    const char (*letter)[6],
    unsigned int x,
    unsigned int y,
    unsigned int color
);

void draw_string_at(
    const char* string,
    unsigned int x,
    unsigned int y,
    unsigned int color
);

void draw_char(
    const char (*letter)[6],
    unsigned int color
);

void print(
    const char* string,
    unsigned int color
);

void println(
    const char* string,
    unsigned int color
);

void debug(
    const char *message,
    const char *caption,
    unsigned int color
);

void new_line();

#endif