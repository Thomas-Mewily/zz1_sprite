#include "base.h"

void window_center_coef(context* c, float coef_x, float coef_y)
{
    SDL_SetWindowPosition(c->window, coef_x*(c->screen_width-c->window_width), (1-coef_y)*(c->screen_height-c->window_height));
}

rectf window_rectf(context* c)
{
    int w; int h;
    SDL_GetWindowSize(c->window, &w, &h);
    return rectanglef(0,0,w,h);
}

rect window_rect(context* c)
{
    int w; int h;
    SDL_GetWindowSize(c->window, &w, &h);
    return rectangle(0,0,w,h);
}