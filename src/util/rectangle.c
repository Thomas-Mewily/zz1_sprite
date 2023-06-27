#include "base.h"

rect rectangle(float x, float y, float w, float h)
{
    rect r;
    r.x = x;
    r.y = y;
    r.w = w;
    r.h = h;
    return r;
}

rect square(float x, float y, float wh) { return rectangle(x, y, wh, wh); }
