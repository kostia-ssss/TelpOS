#include "input.h"

static char buffer[INPUT_MAX];
static size_t length = 0;

void input_init(void)
{
    length = 0;
    buffer[0] = '\0';
}

void input_put(char c)
{
    if (length < INPUT_MAX - 1)
    {
        buffer[length] = c;
        length++;
        buffer[length] = '\0';
    }
}

void input_backspace(void)
{
    if (length == 0)
        return;
    
    length--;
    buffer[length] = '\0';
}

void input_enter(void)
{
    input_put('\n');
    parse_command(buffer);
    input_init();
}

char *input_get(void)
{
    return buffer;
}

size_t input_length(void)
{
    return length;
}