#ifndef DEBUG_H
#define DEBUG_H

#include <stdint.h>
#include "limine.h"
#include "console.h"
#include "colors.h"

void debug(struct limine_framebuffer *fb, 
           uint32_t color, char *caption, char* message);

#endif