#include "shell.h"
#include <stdbool.h>
#include "text/text.h"
#include "text/colors.h"

char buffer[256];
int buffer_pos = 0;

bool compare(char s1[256], char s2[256]) {
    for (int i = 0; s1[i] != '\0'; i++) {
        if (s1[i] != s2[i]) return false;
    }
    return true;
}

void clear_buffer() {
    for (int i = 0; i < 256; i++)
    {
        buffer[i] = '\0';
    }
    
}
void get_char_input(char c) {
    if (buffer_pos >= 255) {
        return;
    }

    buffer[buffer_pos] = c;
    buffer_pos++;

    buffer[buffer_pos] = '\0';
}

void parse_command() {
    if (compare(buffer, "help")) {
        println("Available commands:", WHITE);
        println("help", WHITE);
        println("info", WHITE);
        println("echo", WHITE);
    }
    else if (compare(buffer, "info")) {
        println("TelpOS v0.2.1", WHITE);
        println("!TelpOS is in active developement. There might be some bugs!", YELLOW);
    }
    else if (compare("echo", buffer)) {
        for (int i = 5; buffer[i] != '\0'; i++)
        {
            draw_char(getLetter(buffer[i]), WHITE);
        }
        new_line();
    }
    else {
        println("Unknown command. Type 'help' to see all commands!", RED);
    }
    buffer_pos = 0;
    clear_buffer();
}