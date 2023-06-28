#ifndef CONTEXT_CAMERA_H
#define CONTEXT_CAMERA_H
#include "base.h"

bool camera_load(context* c);
void camera_unload(context* c);

void camera_update(context* c);

void camera_allow_zoom(context* c, bool b);
void camera_allow_scrolling(context* c, bool b);
bool camera_event(context* c, event* ev);

bool camera_can_zoom(context* c);
bool camera_can_scroll(context* c);

#endif