#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "base.h"

typedef SDL_FRect rect;

rect rectangle(float x, float y, float w, float h);
rect square(float x, float y, float wh);

#endif