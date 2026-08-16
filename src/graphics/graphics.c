#include "../graphics/graphics.h"
#include "../graphics/font.h"

size_t get_char_index(char c)
{
    for (size_t i = 0; font_chars[i] != '\0'; i++)
    {
        if (font_chars[i] == c)
            return i;
    }

    return 0;
}

void put_pixel(struct limine_framebuffer *fb,
               size_t x,
               size_t y,
               uint32_t color)
{
    volatile uint32_t *fb_ptr = fb->address;

    fb_ptr[y * (fb->pitch / 4) + x] = color;
}

void draw_rect(struct limine_framebuffer *fb,
               size_t x,
               size_t y,
               size_t w,
               size_t h,
               uint32_t color)
{
    for (size_t i = x; i < x+w; i++)
    {
        for (size_t j = y; j < y+h; j++)
        {
            put_pixel(fb, i, j, color);
        }
    }
}


void draw_char(struct limine_framebuffer *fb,
               size_t letter_x,
               size_t letter_y,
               size_t size,
               uint32_t color,
               char c)
{
    size_t index = get_char_index(c);
    const uint8_t *letter = font[index];

    for (size_t y = 0; y < 7; y++)
    {
        for (size_t x = 0; x < 5; x++)
        {
            if (letter[y] & (1 << (4 - x)))
            {
                draw_rect(
                    fb,
                    letter_x + x * 3 * size,
                    letter_y + y * 3 * size,
                    3 * size,
                    3 * size,
                    color
                );
            }
        }
    }
}

void draw_string(struct limine_framebuffer *fb,
            size_t x,
            size_t y,
            uint32_t color,
            size_t letter_size,
            char* text)
{
    for (size_t i = 0; text[i] != '\0'; i++)
    {
        char c = text[i];

        draw_char(
            fb,
            x + i * 20 * letter_size,
            y,
            letter_size,
            color,
            c
        );
    }
}