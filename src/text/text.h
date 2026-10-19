
#ifndef TEXT_H
#define TEXT_H

#include <limine.h>
#include "letters.h"
#include "draw/draw.h"

const char (*getLetter(char c))[GLYPH_WIDTH];

void init_text_engine(struct limine_framebuffer *_fb);

void draw_char_at(
    const char (*letter)[GLYPH_WIDTH],
    unsigned int x,
    unsigned int y,
    unsigned int color
);

void draw_string_at(
    const char *string,
    unsigned int x,
    unsigned int y,
    unsigned int color
);

void draw_char(
    const char (*letter)[GLYPH_WIDTH],
    unsigned int color
);

void print(const char *string, unsigned int color);
void println(const char *string, unsigned int color);
void debug(const char *message, const char *caption, unsigned int color);
void new_line(void);
void delete_char(void);
void clear(void);

#endif
