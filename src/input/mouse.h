
#ifndef MOUSE_H
#define MOUSE_H

#include <stdbool.h>
#include <stdint.h>

struct mouse {
    int x;
    int y;
    bool left_button;
};

bool mouse_init(void);
bool mouse_try_read_byte(uint8_t *out);

#endif
