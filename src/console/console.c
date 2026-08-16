#include "../console/console.h"
#include "../graphics/graphics.h"
#include "../graphics/colors.h"

static size_t cursor_x;
static size_t cursor_y;

static size_t letter_w;
static size_t letter_h;
static size_t letter_size;
static size_t letter_spacing_x;
static size_t letter_spacing_y;

const uint8_t char_clear[7] = {
    0b01110,
    0b10001,
    0b10001,
    0b11111,
    0b10001,
    0b10001,
    0b10001
};


void console_init(size_t size, size_t spacing_x, size_t spacing_y)
{
    cursor_x = 0;
    cursor_y = 0;

    letter_size = size;
    letter_w = 5 * 3 * size;
    letter_h = 7 * 3 * size;
    letter_spacing_x = spacing_x;
    letter_spacing_y = spacing_y;
}

void putchar_color(struct limine_framebuffer *fb, char c, uint32_t color)
{
    if (c == '\n')
    {
        cursor_x = 0;
        cursor_y += letter_h + letter_spacing_y;
        return;
    }

    draw_char(
        fb,
        cursor_x,
        cursor_y,
        letter_size,
        color,
        c
    );

    cursor_x += letter_w + letter_spacing_x;
}

void putchar(struct limine_framebuffer *fb, char c)
{
    putchar_color(fb, c, WHITE);
}

void print_color(struct limine_framebuffer *fb, char *text, uint32_t color)
{
    for (size_t i = 0; text[i] != '\0'; i++)
    {
        char c = text[i];

        // Перехід на новий рядок
        if (c == '\n')
        {
            cursor_x = 0;
            cursor_y += letter_h + letter_spacing_y;
            continue;
        }

        // Якщо символ не влазить у поточний рядок
        if (cursor_x + letter_w + letter_spacing_x > fb->width)
        {
            cursor_x = 0;
            cursor_y += letter_h;
        }

        // Малюємо один символ
        draw_char(
            fb,
            cursor_x,
            cursor_y,
            letter_size,
            color,
            c
        );

        // Рухаємо курсор вправо
        cursor_x += letter_w + letter_spacing_x;
    }
}

void print(struct limine_framebuffer *fb, char *text)
{
    print_color(fb, text, WHITE);
}

void println_color(struct limine_framebuffer *fb, char *text, uint32_t color)
{
    print_color(fb, text, color);

    cursor_x = 0;
    cursor_y += letter_h + letter_spacing_y;
}

void println(struct limine_framebuffer *fb, char *text)
{
    print(fb, text);

    cursor_x = 0;
    cursor_y += letter_h + letter_spacing_y;
}



void print_at(struct limine_framebuffer *fb,
              size_t x,
              size_t y,
              char *text)
{
    draw_string(
        fb,
        x,
        y,
        letter_size,
        WHITE,
        text
    );
}

void console_clear(struct limine_framebuffer *fb)
{
    draw_rect(
        fb,
        0,
        0,
        fb->width,
        fb->height,
        0x00000000
    );

    cursor_x = 0;
    cursor_y = 0;
}

void delete_previous_char(struct limine_framebuffer *fb)
{
    if (cursor_x < letter_w + letter_spacing_x)
        return;

    cursor_x -= letter_w + letter_spacing_x;

    draw_rect(
        fb,
        cursor_x,
        cursor_y,
        letter_w,
        letter_h,
        BLACK
    );
}