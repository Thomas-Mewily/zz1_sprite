#ifndef CONTEXT_WINDOW_H
#define CONTEXT_WINDOW_H

#include "base.h"

void window_center_coef(context* c, float coef_x, float coef_y);
bool window_load(context* c, char* window_name, int width, int height, Uint32 flags);
void window_unload(context* c);
void window_update(context* c);

rectf window_rectf(context* c);
rect window_rectangle(context* c);

#endif