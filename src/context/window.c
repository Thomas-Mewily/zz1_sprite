#include "base.h"

void window_center_coef(context* c, float coef_x, float coef_y)
{
    SDL_SetWindowPosition(c->window, coef_x*(c->screen_width-c->window_width), (1-coef_y)*(c->screen_height-c->window_height));
}