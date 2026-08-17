#include "shell.h"

struct limine_framebuffer *fb;

void shell_init(struct limine_framebuffer *framebuffer)
{
    fb = framebuffer;
}

int compare(char *buffer, char *word)
{
    size_t i = 0;

    while (word[i] != '\0')
    {
        if (buffer[i] != word[i])
            return 0;

        i++;
    }

    return buffer[i] == '\n' || buffer[i] == '\0';
}

void parse_command(char *buffer)
{
    if (compare(buffer, "hello"))
    {
        println(fb, "Hello! I am Verity, your personal helper friend! Ask me anything - I know everything!");
    }
}