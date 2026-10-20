#include "draw.h"
#include "text/colors.h"

struct limine_framebuffer *fb;

void draw_init(struct limine_framebuffer *_fb) {
    fb = _fb;
}

void draw_pixel(int x, int y, int color) {
    unsigned int *pixels = (unsigned int *)fb->address;
    unsigned int pitch = fb->pitch / 4;

    if (fb != 0 && fb->address != 0 &&
        x >= 0 && y >= 0 &&
        x < fb->width && y < fb->height) {
        pixels[y * pitch + x] = color;
    }
}

void draw_cursor(int x, int y) {
    const int cursor_size = 5;
    const char *cursor[] = {
        "100000000",
        "110000000",
        "111000000",
        "111100000",
        "111110000",
        "111111000",
        "001100000",
        "000100000",
    };

    for (unsigned int row = 0; row < 8; row++) {
        for (unsigned int col = 0; col < 10 - 1; col++) {
            if (cursor[row][col] != '1') {
                continue;
            }

            for (unsigned int dy = 0; dy < cursor_size; dy++) {
                for (unsigned int dx = 0; dx < cursor_size; dx++) {
                    unsigned int px = x + col * cursor_size + dx;
                    unsigned int py = y + row * cursor_size + dy;

                    draw_pixel(px, py, WHITE);
                }
            }
        }
    }
}

void draw_rect(int x, int y, int w, int h, int color) {
    for (int px = x; px < x + w; px++) {
        for (int py = y; py < y + h; py++) {
            draw_pixel(px, py, color);
        }
    }
}

void clear_screen() {
    unsigned int *pixels = (unsigned int *)fb->address;
    unsigned int pitch = fb->pitch / 4;

    for (int y = 0; y < fb->height; y++)
    {
        for (int x = 0; x < fb->width; x++)
        {
            pixels[y * pitch + x] = 0x00000000;
        }
    }
}