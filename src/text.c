#include "text.h"

void drawChar(
    struct limine_framebuffer *fb,
    const char (*letter)[6],
    unsigned int x,
    unsigned int y,
    unsigned int color,
    unsigned int scale
) {
    if (fb == 0 || fb->address == 0 || letter == 0 ||
        scale == 0 || fb->bpp != 32) {
        return;
    }

    unsigned int *pixels = (unsigned int *)fb->address;
    unsigned int pitch = fb->pitch / 4;

    for (unsigned int row = 0; row < 5; row++) {
        for (unsigned int col = 0; col < 5; col++) {
            if (letter[row][col] != '1') {
                continue;
            }

            for (unsigned int dy = 0; dy < scale; dy++) {
                for (unsigned int dx = 0; dx < scale; dx++) {
                    unsigned int px = x + col * scale + dx;
                    unsigned int py = y + row * scale + dy;

                    if (px < fb->width && py < fb->height) {
                        pixels[py * pitch + px] = color;
                    }
                }
            }
        }
    }
}

void drawString(
    struct limine_framebuffer *fb,
    const char* string,
    unsigned int x,
    unsigned int y,
    unsigned int color,
    unsigned int scale
) {
    if (string == 0) {
        return;
    }

    unsigned int curX = x;

    for (int i = 0; string[i] != '\0'; i++) {
        const char (*letter)[6] = getLetter(string[i]);

        if (letter != 0) {
            drawChar(fb, letter, curX, y, color, scale);
        }

        curX += 6 * scale; // 5 пікселів літери + 1 піксель проміжку
    }
}