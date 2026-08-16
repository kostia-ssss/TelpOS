#include "../drivers/keyboard.h"

const char scancode_to_ascii[128] = {
    [0x1E] = 'a',
    [0x30] = 'b',
    [0x2E] = 'c',
    [0x20] = 'd',

    [0x12] = 'e',
    [0x21] = 'f',
    [0x22] = 'g',
    [0x23] = 'h',

    [0x17] = 'i',
    [0x24] = 'j',
    [0x25] = 'k',
    [0x26] = 'l',

    [0x32] = 'm',
    [0x31] = 'n',
    [0x18] = 'o',
    [0x19] = 'p',

    [0x10] = 'q',
    [0x13] = 'r',
    [0x1F] = 's',
    [0x14] = 't',

    [0x16] = 'u',
    [0x2F] = 'v',
    [0x11] = 'w',
    [0x2D] = 'x',

    [0x15] = 'y',
    [0x2C] = 'z',
    [0x39] = ' ',
    [0x02] = '1',

    [0x03] = '2',
    [0x04] = '3',
    [0x05] = '4',
    [0x06] = '5',

    [0x07] = '6',
    [0x08] = '7',
    [0x09] = '8',
    [0x0A] = '9',

    [0x0B] = '0',
    [0x0C] = '-',
    [0x0D] = '=',
    [0x4E] = '+',

    [0x35] = '/',
    [0x37] = '*',
    [0x4A] = '-', //numpad
    [0x1A] = '[',

    [0x1B] = ']',
    [0x2B] = '\\',
    [0x28] = '\'',
    [0x29] = '`',

    [0x34] = '.',
    [0x33] = ',',
    [0x27] = ';',
};

int shift = 0;
const char shift_symbols[] = "!@#$%^&*(){}";

void keyboard_handle(struct limine_framebuffer *fb)
{
    if (inb(0x64) & 1)
    {
        uint8_t scancode = inb(0x60);

        // Shift release
        if (scancode == 0xAA || scancode == 0xB6)
        {
            shift = 0;
            return;
        }

        // Інші release-коди
        if (scancode & 0x80)
            return;

        // Shift press
        if (scancode == 0x2A || scancode == 0x36)
        {
            shift = 1;
            return;
        }

        if (scancode == 0x1C) // Enter
        {
            putchar(fb, '\n');
            return;
        }

        if (scancode == 0x0E)
        {
            delete_previous_char(fb);
            return;
        }

        char c = scancode_to_ascii[scancode];

        if (c != 0)
        {
            if (shift)
            {
                if (c >= 'a' && c <= 'z')
                    c -= 32;

                if (c >= '1' && c <= '9')
                    c = shift_symbols[c - '1'];

                if (c == '0')
                    c = ')';
                
                if (c == '[')
                    c = '{';
                
                if (c == ']')  
                    c = '}';

                if (c == '\\')
                    c = '|';

                if (c == ',')
                    c = '<';
                
                if (c == '.')
                    c = '>';
                
                if (c == '/')
                    c = '?';

                if (c == '`')
                    c = '~';
                
                if (c == '\'')
                    c = '"';
                
                if (c == ';')
                    c = ':';
                
                if (c == '=')
                    c = '+';
            }

            putchar(fb, c);
        }
    }
}