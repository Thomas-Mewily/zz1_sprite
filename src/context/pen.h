#ifndef CONTEXT_PEN_H
#define CONTEXT_PEN_H
#include "base.h"

#define PEN_MODE_HOLLOW 0x1
#define PEN_MODE_FILLED 0x2
#define PEN_MODE_FILL PEN_MODE_FILLED


#define FONT_SIZE_MAX_NB_SCREEN_HEIGHT(nb) (c->screen_height/((float)nb)/(camera_scale_y(c)))
#define FONT_SIZE_SMALL      FONT_SIZE_MAX_NB_SCREEN_HEIGHT(32)
#define FONT_SIZE_NORMAL     FONT_SIZE_MAX_NB_SCREEN_HEIGHT(16)
#define FONT_SIZE_BIG        FONT_SIZE_MAX_NB_SCREEN_HEIGHT(10)
#define FONT_SIZE_FULLSCREEN FONT_SIZE_MAX_NB_SCREEN_HEIGHT(2)


void pen_color(context* c, color co);
color pen_get_color(context* c);

void pen_clear(context* c);

void pen_mode(context* c, uint32 mode);



void pen_texture(context* c, texture* t, rect src, rectf dest);
void pen_texture_at(context* c, texture* t, rect src, float x, float y, float scaleX, float scaleY);
void pen_texture_at_center(context* c, texture* t, rect src, float x, float y, float scaleX, float scaleY, float coef_centerX, float coef_centerY);

void pen_animation_at(context* c, animation* a, float x, float y, float scaleX, float scaleY, time t);
void pen_animation_at_center(context* c, animation* a, float x, float y, float scaleX, float scaleY, float coef_centerX, float coef_centerY, time t);
void pen_animation(context* c, animation* a, rectf dest, time t);

/*
bool pen_is_down(context*  c);
void pen_down(context* c);
void pen_up(context* c);

void pen_goto(context* c, float x, float y);
void pen_goto_with_color(context* c, float x, float y, color co);
void pen_move(context* c, float step);
void pen_rotate(context* c, angle a);
*/

void pen_rect(context* c, rectf r);
void pen_line(context* c, float x1, float y1, float x2, float y2);
void pen_dot(context* c, float x, float y);

void pen_pixel(context* c, float x, float y);
void pen_pixel_line(context* c, float x1, float y1, float x2, float y2);
void pen_pixel_rect(context* c, rectf r);

void pen_oval(context* c, float x, float y, float radius_x, float radius_y);
void pen_circle(context* c, float x, float y, float radius);
void pen_triangle_colored(context* c,
                            float x1, float y1, color c1,
                            float x2, float y2, color c2,
                            float x3, float y3, color c3
                         ); 
void pen_triangle(context* c,
                            float x1, float y1,
                            float x2, float y2,
                            float x3, float y3
                ); 

void pen_text_at(context* c, char* text, float x, float y, float pixel_ligne_height);
void pen_text_at_center(context* c, char* text, float x, float y, float pixel_ligne_height, float centerX, float centerY);

#define pen_formatted_text_at_center(context, x, y, pixel_ligne_height, centerX, centerY, format, ...)\
{\
   char s[2048]; \
   sprintf(s, format, __VA_ARGS__);\
   pen_text_at_center(c, s, x, y, pixel_ligne_height, centerX, centerY);\
}

void pen_char_at(context* c, char letter, float x, float y, float pixel_ligne_height);
void pen_char(context* c, char letter, rectf dest);


void pen_graph(context* c, graph* g);
void pen_join (context* c, graph* g, int a, int b);
void pen_node (context* c, graph* g, int idx);

bool pen_load(context* c);
void pen_unload(context* c);

void pen_draw_trajet(context* c, graph* g, trajet* t);
// return join length
//float pen_draw_join_direction(context* c, graph* g, int a, int b);
#endif