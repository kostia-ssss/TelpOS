#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include "io.h"
#include "../console/console.h"
#include "../input/input.h"
#include "../debug/debug.h"

void keyboard_handle(struct limine_framebuffer *fb);

#endif