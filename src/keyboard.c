#include "text.h"
#include "keyboard.h"
#include "io.h"
#include "colors.h"

static const char scancode_to_ascii[128] = {
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
    [0x0F] = '\t',  // Tab

    

    [0x10] = 'q',
    [0x11] = 'w',
    [0x12] = 'e',
    [0x13] = 'r',
    [0x14] = 't',
    [0x15] = 'y',
    [0x16] = 'u',
    [0x17] = 'i',
    [0x18] = 'o',
    [0x19] = 'p',
    [0x1A] = '[',  
    [0x1B] = ']',  

    [0x1E] = 'a',
    [0x1F] = 's',
    [0x20] = 'd',
    [0x21] = 'f',
    [0x22] = 'g',
    [0x23] = 'h',
    [0x24] = 'j',
    [0x25] = 'k',
    [0x26] = 'l',
    [0x27] = ';',   
    [0x28] = '\'', 
    [0x29] = '`', 
    [0x2B] = '\\',  // backslash

    [0x2C] = 'z',
    [0x2D] = 'x',
    [0x2E] = 'c',
    [0x2F] = 'v',
    [0x30] = 'b',
    [0x31] = 'n',
    [0x32] = 'm',
    [0x33] = ',',
    [0x34] = '.',
    [0x35] = '/', 
    [0x39] = ' ',
};

static const char shift_symbols[128] = {
    ['1'] = '!',
    ['2'] = '@',
    ['3'] = '#',
    ['4'] = '$',
    ['5'] = '%',
    ['6'] = '^',
    ['7'] = '&',
    ['8'] = '*',
    ['9'] = '(',
    ['0'] = ')',
    ['-'] = '_',
    ['='] = '+',
    ['.'] = '>',
    [','] = '<',
    ['[']  = '{',
    [']']  = '}',
    [';']  = ':',
    ['\''] = '"',
    ['`']  = '~',
    ['\\'] = '|',
    ['/']  = '?',
};

bool shift = false;
bool caps = false;

bool keyboard_poll(uint8_t *scancode) {
    if ((inb(0x64) & 1) == 0) {
        return false;
    }

    uint8_t code = inb(0x60);

    // Ignore key-release codes in PS/2 Set 1.
    if ((code & 0x80) && code != 0xAA && code != 0xB6) {
        return false;
    }

    *scancode = code;
    return true;
}

char keyboard_to_ascii(uint8_t scancode) {
    if (scancode == 0xAA || scancode == 0xB6) { // Shift release
        shift = false;
    }

    if (scancode >= 128) {
        return '\0';
    }

    if (scancode == 0x1C) { // Enter
        new_line();
    }

    if (scancode == 0x2A || scancode == 0x36) { // Shift
        shift = true;
    }

    if (scancode == 0x3A) { // Capslock
        caps = !caps;
    }

    if (scancode == 0x0E) { // Backspace
        delete_char();
    }
        
    

    char c = scancode_to_ascii[scancode];

    if (shift ^ caps) {
        if (c >= 'a' && c <= 'z') {
            c -= 'a' - 'A';
        }
        else {
            c = shift_symbols[c];
        }
    }

    return c;
}
