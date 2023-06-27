#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "base.h"

typedef SDL_FRect rectf;
rectf rectanglef(float x, float y, float w, float h);
rectf squaref(float x, float y, float wh);

typedef SDL_Rect rect;
rect rectangle(int x, int y, int w, int h);
rect square(int x, int y, int wh);

#endif