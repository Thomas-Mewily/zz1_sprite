#include "base.h"

void pen_goto(context* c, float x, float y) 
{ 
    c->pen_x = x; c->pen_y = y;
    if(pen_is_down(c))
    {
        c->_pen_idx++;
        //(c->_pen_vertex[c->_pen_idx]).position.x = x;
        //(c->_pen_vertex[c->_pen_idx]).position.y = y;

        //(c->_pen_vertex[c->_pen_idx]).color = to_sdl_color(p);
    }
}
void pen_goto_with_color(context* c, float x, float y, color co)
{
    pen_goto(c, x, y);
    pen_color(c, co);
}

void pen_move(context* c, float step) 
{ 
    pen_goto(c, c->pen_x + cos(c->pen_move_rotation)*step, c->pen_y + sin(c->pen_move_rotation)*step);
}
void pen_mode(context* c, uint32 mode)
{
    c->pen_mode = mode;
}


void pen_move_2D(context* c, float stepX, float stepY) 
{
    float cosinus = cos(c->pen_move_rotation);
    float sinus   = sin(c->pen_move_rotation);

    // not sure about that
    c->pen_x += cosinus*stepX + sinus  *stepY;
    c->pen_y += sinus  *stepX + cosinus*stepY;
}

void pen_rotate(context* c, angle a)
{
    c->pen_move_rotation += a;
}

void pen_color(context* c, color co) 
{ 
    SDL_SetRenderDrawColor(c->renderer, co.r, co.g, co.b, co.a);
    if(pen_is_down(c))
    {
        (c->_pen_vertex[c->_pen_idx]).color = to_sdl_color(co);
    }
}
color pen_get_color(context* c)
{
    color co;
    SDL_GetRenderDrawColor(c->renderer, &co.r, &co.g, &co.b, &co.a);
    return co;
}

void pen_clear(context* c) { SDL_RenderClear(c->renderer); }

// todo : affected by pen size
void pen_line(context* c, float x1, float y1, float x2, float y2) { pen_pixel_line(c, x1, y1, x2, y2); }
void pen_dot(context* c, float x, float y) { pen_pixel(c, x, y); }
void pen_rect(context* c, rectf r) { pen_pixel_rect(c, r); }

#define X(x) apply_x_offset(c, x)
#define Y(y) apply_y_offset(c, y)

float apply_x_offset(context* c, float x) { return (x-c->pen_x)*c->pen_scale; }
float apply_y_offset(context* c, float y) { return (y-c->pen_y)*c->pen_scale; }

rectf apply_offset(context* c, rectf r)
{
    return rectanglef(X(r.x), Y(r.y), r.w*c->pen_scale, r.h*c->pen_scale);
}

void pen_pixel(context* c, float x, float y) { SDL_RenderDrawPointF(c->renderer, X(x), Y(y)); }
void pen_pixel_line(context* c, float x1, float y1, float x2, float y2) { SDL_RenderDrawLineF(c->renderer, X(x1), Y(y1), X(x2), Y(y2)); }
void pen_pixel_rect(context* c, rectf r) { r = apply_offset(c, r); SDL_RenderFillRectF(c->renderer, &r); }
void pen_circle(context* c, float x, float y, float radius) { pen_oval(c, x, y, radius, radius); }
void pen_oval(context* c, float x, float y, float radius_x, float radius_y)
{
    if((c->pen_mode) & PEN_MODE_FILLED)
    {
        int stepPrecision = 2;
        for(int rx = 0; rx <= radius_x; rx+=stepPrecision)
        {
            int height = ((float)(radius_y))*sqrt(1-(1-rx/(float)radius_x)*(1-rx/(float)radius_x));
            pen_rect(c, rectanglef(x-radius_x+rx,y-height, stepPrecision, 2*height));
            pen_rect(c, rectanglef(x+radius_x-rx,y-height, stepPrecision, 2*height));
        }
    }else if((c->pen_mode) & PEN_MODE_HOLLOW)
    {
        int precision = (int)sqrt((radius_x*radius_y)/10)+4;
        if(precision > 0)
        {
            #define PEN_DRAW_CIRCLE_MAX_PRECISION 500
            if(precision > PEN_DRAW_CIRCLE_MAX_PRECISION){ precision = PEN_DRAW_CIRCLE_MAX_PRECISION; }
            int old_x = radius_x;
            int old_y = 0;
            angle a = from_degree(0);

            for(int i = 0;i <= precision;i++)
            {
                a += from_degree(360.0f/precision);

                int new_x = cos(a)*radius_x;
                int new_y = sin(a)*radius_y;
                pen_line(c, x+old_x, y+old_y, x+new_x, y+new_y);
                old_x = new_x;
                old_y = new_y;
            }
        }
    }
}
/*
void pen_triangle(context* c, float x1, float y1,
                              float x2, float y2,
                              float x3, float y3
                 )
{
    color co;
    SDL_GetRenderDrawColor(c->renderer, &co.r, &co.g, &co.b, &co.a);
    return pen_triangle_colored(c, x1, y1, co, x2, y2, co, x3, y3, co);
}

void pen_triangle_colored(context* c, float x1, float y1, color c1,
                              float x2, float y2, color c2,
                              float x3, float y3, color c3
                 )
{
    // Thank to https://stackoverflow.com/questions/69447778/fastest-way-to-draw-filled-quad-triangle-with-the-sdl2-renderer
    vertex triangleVertex[3]=
    {
        create_vertex(X(x1), Y(y1), c1),
        create_vertex(X(x2), Y(y2), c2),
        create_vertex(X(x3), Y(y3), c3),
    };

    if( SDL_RenderGeometry(c->renderer, NULL, triangleVertex, 3, NULL, 0) < 0 ) {SDL_Log("%s\n", SDL_GetError());}
}*/

bool pen_is_down(context*  c)
{
    return c->_pen_is_down;
}
void pen_down(context* c)
{
    check(c->_pen_is_down == false);
    c->_pen_is_down = true;
    c->_pen_idx = 0;
}
void pen_up(context* c)
{
    check(c->_pen_is_down == true);
    c->_pen_is_down = false;
}

void pen_texture(context* c, texture* t, rect src, rectf dest)
{
    SDL_RenderCopyF(c->renderer, t, &src, &dest);
}

void pen_texture_at(context* c, texture* t, rect src, float x, float y, float scaleX, float scaleY)
{
    pen_texture(c, t, src, rectanglef(x, y, texture_width(t)*scaleX,  texture_height(t)*scaleY));
}

void pen_texture_at_center(context* c, texture* t, rect src, float x, float y, float scaleX, float scaleY, float coef_centerX, float coef_centerY)
{
    float frame_width_scaled =  texture_width (t) *scaleX;
    float frame_height_scaled = texture_height(t) *scaleY;
    pen_texture(c, t, src, rectanglef(x-frame_width_scaled*coef_centerX, y-frame_height_scaled*coef_centerY, frame_width_scaled,  frame_height_scaled));
}


void pen_animation_at(context* c, animation* a, float x, float y, float scaleX, float scaleY, time t)
{
    if( !a->nb_frame ) return;
    pen_animation(c, a, rectanglef(x, y, texture_width(a->sprite_sheet->t)/a->nb_frame*scaleX, texture_height(a->sprite_sheet->t)*scaleY), t);
}

void pen_animation_at_center(context* c, animation* a, float x, float y, float scaleX, float scaleY, float coef_centerX, float coef_centerY, time t)
{
    float frame_width_scaled =  animation_width (a) *scaleX;
    float frame_height_scaled = animation_height(a) *scaleY;
    pen_animation(c, a, rectanglef(x-frame_width_scaled*coef_centerX, y-frame_height_scaled*coef_centerY, frame_width_scaled, frame_height_scaled), t);
}

void pen_animation(context* c, animation* a, rectf dest, time t)
{
    pen_texture(c, a->sprite_sheet->t, *animation_get_frame(a, t), dest);
}

void pen_text(context* c, const char* text, rectf dest)
{
    
}