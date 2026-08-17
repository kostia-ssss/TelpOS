#ifndef SHELL_H
#define SHELL_H

#include <stdint.h>
#include "../console/console.h"
#include "../input/input.h"
#include "../debug/debug.h"
#include "../boot/limine.h"

void shell_init(struct limine_framebuffer *fb);
void parse_command(char *buffer);

#endif