#include "text.h"
#include "colors.h"
#include "letters.h"

int cursorX = 0;
int cursorY = 0;
int letterSize = 3;

void init_text_engine(struct limine_framebuffer *_fb) {
    draw_init(_fb);
}

void draw_char_at(
    const char (*letter)[GLYPH_WIDTH],
    unsigned int x,
    unsigned int y,
    unsigned int color
) {
    if (letter == 0 || letterSize == 0) {
        return;
    }

    for (unsigned int row = 0; row < GLYPH_HEIGHT; row++) {
        for (unsigned int col = 0; col < GLYPH_WIDTH - 1; col++) {
            if (letter[row][col] != '1') {
                continue;
            }

            for (unsigned int dy = 0; dy < letterSize; dy++) {
                for (unsigned int dx = 0; dx < letterSize; dx++) {
                    unsigned int px = x + col * letterSize + dx;
                    unsigned int py = y + row * letterSize + dy;

                    draw_pixel(px, py, color);
                }
            }
        }
    }
}

void draw_char(
    const char (*letter)[GLYPH_WIDTH],
    unsigned int color) {
        draw_char_at(
            letter,
            cursorX * (GLYPH_WIDTH - 1 + 1) * letterSize,
            cursorY * (GLYPH_HEIGHT + 1) * letterSize,
            color
        );
        cursorX++;
        if (cursorX > 40) {
            cursorX = 0;
            cursorY++;
        }
}

void draw_string_at(
    const char *string,
    unsigned int x,
    unsigned int y,
    unsigned int color
) {
    if (string == 0) {
        return;
    }

    unsigned int curX = x;

    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == ' ') {
            curX += 8 * letterSize;
            continue;
        }

        const char (*letter)[GLYPH_WIDTH] = getLetter(string[i]);

        if (letter != 0) {
            draw_char_at(letter, curX, y, color);
        }

        curX += 8 * letterSize;
    }
}

void print(
    const char *string,
    unsigned int color
) {
    if (string == 0) {
        return;
    }

    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == ' ') {
            cursorX++;
        } else if (string[i] == '\t') {
            cursorX += 4;
        } else {
            const char (*letter)[GLYPH_WIDTH] = getLetter(string[i]);

            if (letter != 0) {
                draw_char(letter, color);
            }
        }

        if (cursorX == 40) {
            cursorX = 0;
            cursorY++;
        }
    }
}

void clear() {
    clear_screen();
    
    cursorX = 0;
    cursorY = 0;
}

void new_line() {
    cursorX = 0;
    cursorY++;
}

void println(
    const char *string,
    unsigned int color
) {
    print(string, color);
    new_line();
}

void delete_char() {
    char black[7][8] = {
        "1111111",
        "1111111",
        "1111111",
        "1111111",
        "1111111",
        "1111111",
        "1111111",
    };

    cursorX--;
    draw_char(black, BLACK);
    cursorX--;
}

void debug(
    const char *message,
    const char *caption,
    unsigned int color
) {
    print("[", color);
    print(caption, color);
    print("] ", color);
    println(message, color);
}