
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

bool keyboard_poll(uint8_t *scancode);
char keyboard_to_ascii(uint8_t scancode);

#endif
