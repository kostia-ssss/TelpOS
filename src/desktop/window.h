#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

typedef struct {
    int x;
    int y;
    int w;
    int h;
} Window;

Window create_window(int x, int y, int w, int h);
void draw_window(Window window);

#endif