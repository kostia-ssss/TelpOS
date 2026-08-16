#ifndef DEBUG_H
#define DEBUG_H

#include <stdint.h>
#include "../boot/limine.h"
#include "../console/console.h"
#include "../graphics/colors.h"

void debug(struct limine_framebuffer *fb, 
           uint32_t color, char *caption, char* message);

#endif