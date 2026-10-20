#include "window.h"
#include "draw/draw.h"
#include "text/colors.h"

Window create_window(int x, int y, int w, int h) {
    Window window = {x, y, w, h};
    return window;
}

void draw_window(Window window) {
    draw_rect(window.x, window.y, window.w, window.h, GREY);
    draw_rect(window.x + window.w - 30, window.y, 30, 25, RED);
}