#include "text.h"
#include "colors.h"

int cursorX = 0;
int cursorY = 0;
int letterSize = 3;
struct limine_framebuffer *fb;

void init_text_engine(struct limine_framebuffer *_fb) {
    fb = _fb;
}

void draw_char_at(
    const char (*letter)[6],
    unsigned int x,
    unsigned int y,
    unsigned int color
) {
    if (fb == 0 || fb->address == 0 || letter == 0 ||
        letterSize == 0 || fb->bpp != 32) {
        return;
    }

    unsigned int *pixels = (unsigned int *)fb->address;
    unsigned int pitch = fb->pitch / 4;

    for (unsigned int row = 0; row < 5; row++) {
        for (unsigned int col = 0; col < 5; col++) {
            if (letter[row][col] != '1') {
                continue;
            }

            for (unsigned int dy = 0; dy < letterSize; dy++) {
                for (unsigned int dx = 0; dx < letterSize; dx++) {
                    unsigned int px = x + col * letterSize + dx;
                    unsigned int py = y + row * letterSize + dy;

                    if (px < fb->width && py < fb->height) {
                        pixels[py * pitch + px] = color;
                    }
                }
            }
        }
    }
}

void draw_char(
    const char (*letter)[6],
    unsigned int color) {
        draw_char_at(letter, cursorX * 5 * (letterSize + 1), cursorY * 5 * (letterSize + 1), color);
        cursorX++;
        if (cursorX > 64) {
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
    if (fb == 0 || string == 0) {
        return;
    }

    unsigned int curX = x;

    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == ' ') {
            curX += 6 * letterSize;
            continue;
        }

        const char (*letter)[6] = getLetter(string[i]);

        if (letter != 0) {
            draw_char_at(letter, curX, y, color);
        }

        curX += 6 * letterSize;
    }
}

void print(
    const char *string,
    unsigned int color
) {
    if (fb == 0 || string == 0) {
        return;
    }

    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == ' ') {
            cursorX++;
        } else if (string[i] == '\t') {
            cursorX += 4;
        } else {
            const char (*letter)[6] = getLetter(string[i]);

            if (letter != 0) {
                draw_char(letter, color);
            }
        }

        if (cursorX == 64) {
            cursorX = 0;
            cursorY++;
        }
    }
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
    char black[5][6] = {
        "11111",
        "11111",
        "11111",
        "11111",
        "11111",
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