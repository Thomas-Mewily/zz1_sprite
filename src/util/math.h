#ifndef MATH_H
#define MATH_H
#include <math.h>

#define sqrt(val_float)  (sqrtf)(val_float)
#define pow(x_float, y_float) (powf)(x_float,y_float)
#define abs(val_float) (fabsf)(val_float)

float squared(float x);

float length(float x1, float y1, float x2, float y2);
float length_squared(float x1, float y1, float x2, float y2);

#endif