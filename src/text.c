#include "text.h"

int cursorX = 0;
int cursorY = 0;
int letterSize = 3;

void draw_char_at(
    struct limine_framebuffer *fb,
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

void draw_string_at(
    struct limine_framebuffer *fb,
    const char* string,
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
            draw_char(fb, letters[26], color);
            continue;
        }

        const char (*letter)[6] = getLetter(string[i]);

        if (letter != 0) {
            draw_char(fb, letter, color);
        }
    }
}

void draw_char(
    struct limine_framebuffer *fb,
    const char (*letter)[6],
    unsigned int color) {
        draw_char_at(fb, letter, cursorX * 5 * (letterSize + 1), cursorY * 5 * (letterSize + 1), color);
        cursorX++;
        if (cursorX > 80) {
            cursorX = 0;
            cursorY++;
        }
}

void print(
    struct limine_framebuffer *fb,
    const char* string,
    unsigned int color
) {
    if (string == 0) 
        return;

    for (int i = 0; string[i] != '\0'; i++) {
        if (string[i] == ' ') {
            draw_char(fb, letters[26], color);
            continue;
        }

        const char (*letter)[6] = getLetter(string[i]);

        if (letter != 0) {
            draw_char(fb, letter, color);
        }
    }
}

void println(struct limine_framebuffer *fb,
    const char* string,
    unsigned int color) {
        print(fb, string, color);
        cursorX = 0;
        cursorY++;
}