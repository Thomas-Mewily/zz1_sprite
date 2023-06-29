#include "base.h"

float camera_x(context* c) { return c->camera_x; }
float camera_y(context* c) { return c->camera_y;}
float camera_scale_x(context* c) { return c->camera_scale_x;}
float camera_scale_y(context* c) { return c->camera_scale_y;}

void camera_set_x(context* c, float v) { c->camera_x = v; }
void camera_set_y(context* c, float v) { c->camera_y = v; }
void camera_set_scale_x(context* c, float v) { c->camera_scale_x = v; }
void camera_set_scale_y(context* c, float v) { c->camera_scale_y = v; }

bool camera_load(context* c)
{
    camera_set_x(c, 0);
    camera_set_y(c, 0);
    camera_set_scale_x(c, 1);
    camera_set_scale_y(c, 1);

    bool allow = true;
    camera_allow_scrolling(c, allow);
    camera_allow_zoom(c, allow);
    return true;
}

void camera_unload(context* c){ UNUSED(c); }

void camera_update(context* c)
{
    if(c->mouse_left_button_down)
    {
        c->camera_x -= c->mouse_delta_x/c->camera_scale_x;
        c->camera_y -= c->mouse_delta_y/c->camera_scale_y;
    }
}

void camera_zoom(context* c, float center_pixel_x, float center_pixel_y, float coef)
{
    float center_coef_x = center_pixel_x /(float)window_width(c);
    float center_coef_y = center_pixel_y /(float)window_height(c);

    float new_scale_x = c->camera_scale_x*coef;
    float new_scale_y = c->camera_scale_y*coef;

    float offset_x = (1-coef) * window_width(c);
    float offset_y = (1-coef) * window_height(c);

    c->camera_x -= (offset_x*center_coef_x)/new_scale_x;
    c->camera_y -= (offset_y*center_coef_y)/new_scale_y;

    c->camera_scale_x = new_scale_x;
    c->camera_scale_y = new_scale_y;
}

bool camera_event(context* c, event* ev)
{
    if(camera_can_zoom(c))
    {
        if(ev->type == SDL_MOUSEWHEEL)
        {
            #define coef (1+0.1f *ev->wheel.y)
            if(ev->wheel.y > 0) // scroll up
            {
                camera_zoom(c, input_mouse_x(c), input_mouse_y(c), coef);
                // Put code for handling "scroll up" here!
            }
            else if(ev->wheel.y < 0) // scroll down
            {
                camera_zoom(c, input_mouse_x(c), input_mouse_y(c), coef);
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
            if(camera_can_scroll(c))
            {
                //camera_set_x(input_mouse_x(c))
                //c->_camera_x += (c->mouse_old_x-c->mouse_x); ///c->_camera_scale_x;
                //c->_camera_y += (c->mouse_old_y-c->mouse_y); ///c->_camera_scale_y;
            }
            // ... handle mouse clicks ...
        }
    }

    return false;
}


void camera_allow_zoom(context* c, bool b)
{
    c->camera_can_zoom = b;
}
void camera_allow_scrolling(context* c, bool b)
{
    c->camera_can_scroll = b;
}

bool camera_can_zoom(context* c) { return c->camera_can_zoom; }
bool camera_can_scroll(context* c) { return c->camera_can_scroll; }

camera_state camera_get_state(context* c)
{   
    camera_state s;
    s.x = c->camera_x;
    s.y = c->camera_y;
    s.scale_x = c->camera_scale_x;
    s.scale_y = c->camera_scale_y;
    return s;
}

void camera_set_state(context* c, camera_state s)
{
    c->camera_x = s.x;
    c->camera_y= s.y;
    c->camera_scale_x = s.scale_x;
    c->camera_scale_y = s.scale_y;
}