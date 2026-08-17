#ifndef INPUT_H
#define INPUT_H

#include <stddef.h>
#include <stdint.h>
#include "../boot/limine.h"
#include "../shell/shell.h"

#define INPUT_MAX 256

void input_init(void);

void input_put(char c);
void input_backspace(void);
void input_enter(void);

char *input_get(void);
size_t input_length(void);

#endif