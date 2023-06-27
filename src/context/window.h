#ifndef CONTEXT_WINDOW_H
#define CONTEXT_WINDOW_H

#include "base.h"

void window_center_coef(context* c, float coef_x, float coef_y);

rectf window_rectf(context* c);
rect window_rectangle(context* c);

#endif