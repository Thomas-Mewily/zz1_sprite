#include "base.h"

bool camera_load(context* c)
{
    c->_camera_x = 0;
    c->_camera_y = 0;
    c->_camera_scale_x = 1;
    c->_camera_scale_y = 1;

    bool allow = false;
    camera_allow_scrolling(c, allow);
    camera_allow_zoom(c, allow);
    return true;
}

void camera_unload(context* c){ UNUSED(c); }

void camera_update(context* c)
{
    if(camera_can_scroll(c))
    {
        c->_camera_x += (c->mouse_old_x-c->mouse_x); ///c->_camera_scale_x;
        c->_camera_y += (c->mouse_old_y-c->mouse_y); ///c->_camera_scale_y;
    }
}

bool camera_event(context* c, event* ev)
{
    if(camera_can_zoom(c))
    {
        if(ev->type == SDL_MOUSEWHEEL)
        {
            #define coef 1.01
            if(ev->wheel.y > 0) // scroll up
            {
                c->_camera_scale_x = c->_camera_scale_x*coef;
                c->_camera_scale_y = c->_camera_scale_x;
                // Put code for handling "scroll up" here!
            }
            else if(ev->wheel.y < 0) // scroll down
            {
                c->_camera_scale_x = c->_camera_scale_x/coef;
                c->_camera_scale_y = c->_camera_scale_x;
            }

            if(ev->wheel.x > 0) // scroll right
            {
                // ...
            }
            else if(ev->wheel.x < 0) // scroll left
            {
                // ...
            }
        }
        else if(ev->type == SDL_MOUSEBUTTONDOWN)
        {
            // ... handle mouse clicks ...
        }
    }

    return false;
}


void camera_allow_zoom(context* c, bool b)
{
    c->_camera_can_zoom = b;
}
void camera_allow_scrolling(context* c, bool b)
{
    c->_camera_can_scroll = b;
}

bool camera_can_zoom(context* c) { return c->_camera_can_zoom; }
bool camera_can_scroll(context* c) { return c->_camera_can_scroll; }