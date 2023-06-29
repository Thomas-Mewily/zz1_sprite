#ifndef CONTEXT_CAMERA_H
#define CONTEXT_CAMERA_H
#include "base.h"

typedef struct
{
    float x;
    float y;
    float scale_x;
    float scale_y;
}camera_state;

camera_state camera_get_state(context* c);
void camera_set_state(context* c, camera_state s);

bool camera_load(context* c);
void camera_unload(context* c);

void camera_update(context* c);

void camera_allow_zoom(context* c, bool b);
void camera_allow_scrolling(context* c, bool b);
bool camera_event(context* c, event* ev);

float camera_x(context* c);
float camera_y(context* c);
float camera_scale_x(context* c);
float camera_scale_y(context* c);

void camera_set_x(context* c, float v);
void camera_set_y(context* c, float v);
void camera_set_scale_x(context* c, float v);
void camera_set_scale_y(context* c, float v);

bool camera_can_zoom(context* c);
bool camera_can_scroll(context* c);

#endif