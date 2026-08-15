#include "keyboard.h"

const char scancode_to_ascii[128] = {
    [0x1E] = 'A',
    [0x30] = 'B',
    [0x2E] = 'C',
    [0x20] = 'D',

    [0x12] = 'E',
    [0x21] = 'F',
    [0x22] = 'G',
    [0x23] = 'H',

    [0x17] = 'I',
    [0x24] = 'J',
    [0x25] = 'K',
    [0x26] = 'L',

    [0x32] = 'M',
    [0x31] = 'N',
    [0x18] = 'O',
    [0x19] = 'P',

    [0x10] = 'Q',
    [0x13] = 'R',
    [0x1F] = 'S',
    [0x14] = 'T',

    [0x16] = 'U',
    [0x2F] = 'V',
    [0x11] = 'W',
    [0x2D] = 'X',

    [0x15] = 'Y',
    [0x2C] = 'Z',
    [0x39] = ' ',
};

void keyboard_handle(struct limine_framebuffer *fb)
{
    if (inb(0x64) & 1)
    {
        uint8_t scancode = inb(0x60);

        // Key release
        if (scancode & 0x80)
            return;
        
        if (scancode == 0x1C) // Enter
        {
            putchar(fb, '\n');
        }

        if (scancode == 0x0E) // Backspace
        {
            
        }

        char c = scancode_to_ascii[scancode];

        if (c != 0)
        {
            putchar(fb, c);
        }
        
    }
}