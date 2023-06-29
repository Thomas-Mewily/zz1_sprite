#include "base.h"

#define renderer window_renderer(c)

void pen_mode(context* c, uint32 mode)
{
    c->pen_mode = mode;
}

void pen_color(context* c, color co) 
{ 
    SDL_SetRenderDrawColor(renderer , co.r, co.g, co.b, co.a);
    /*
    if(pen_is_down(c))
    {
        (c->_pen_vertex[c->_pen_idx]).color = to_sdl_color(co);
    }
    */
}
color pen_get_color(context* c)
{
    color co;
    SDL_GetRenderDrawColor(renderer, &co.r, &co.g, &co.b, &co.a);
    return co;
}

void pen_clear(context* c) { SDL_RenderClear(renderer); }

// todo : affected by pen size
void pen_line(context* c, float x1, float y1, float x2, float y2) { pen_pixel_line(c, x1, y1, x2, y2); }
void pen_dot(context* c, float x, float y) { pen_pixel(c, x, y); }
void pen_rect(context* c, rectf r) { pen_pixel_rect(c, r); }

#define X(x) apply_x_offset(c, x)
#define Y(y) apply_y_offset(c, y)

float apply_x_offset(context* c, float x) { return (x - camera_x(c))*camera_scale_x(c); }
float apply_y_offset(context* c, float y) { return (y - camera_y(c))*camera_scale_y(c); }

rectf apply_offset(context* c, rectf r)
{
    return rectanglef(X(r.x), Y(r.y), r.w*camera_scale_x(c), r.h*camera_scale_y(c));
}

void pen_pixel(context* c, float x, float y) { SDL_RenderDrawPointF(renderer, X(x), Y(y)); }
void pen_pixel_line(context* c, float x1, float y1, float x2, float y2) { SDL_RenderDrawLineF(renderer, X(x1), Y(y1), X(x2), Y(y2)); }
void pen_pixel_rect(context* c, rectf r) { r = apply_offset(c, r); SDL_RenderFillRectF(renderer, &r); }
void pen_circle(context* c, float x, float y, float radius) { pen_oval(c, x, y, radius, radius); }
void pen_oval(context* c, float x, float y, float radius_x, float radius_y)
{
    if((c->pen_mode) & PEN_MODE_FILLED)
    {
        int stepPrecision = 2;
        for(int rx = 0; rx <= radius_x+1; rx+=stepPrecision)
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

#if 0
/*
void pen_move_2D(context* c, float stepX, float stepY) 
{
    
    //float cosinus = cos(c->pen_move_rotation);
    //float sinus   = sin(c->pen_move_rotation);

    // not sure about that
    //c->pen_x += cosinus*stepX + sinus  *stepY;
    //c->pen_y += sinus  *stepX + cosinus*stepY;
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

void pen_rotate(context* c, angle a)
{
    c->pen_move_rotation += a;
}
#endif

void pen_texture(context* c, texture* t, rect src, rectf dest)
{
    dest = apply_offset(c, dest);
    SDL_RenderCopyF(renderer, t, &src, &dest);
}

void pen_texture_at(context* c, texture* t, rect src, float x, float y, float scaleX, float scaleY)
{
    pen_texture(c, t, src, rectanglef(x, y, src.w*scaleX,  src.h*scaleY));
}

void pen_texture_at_center(context* c, texture* t, rect src, float x, float y, float scaleX, float scaleY, float coef_centerX, float coef_centerY)
{
    float frame_width_scaled =  src.w *scaleX;
    float frame_height_scaled = src.h *scaleY;
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


#define NUM_COL_LETTER 16
#define LETTER_WIDTH  18
#define LETTER_HEIGHT 18
#define INTERLIGNE 0.2
#define LETTER_SPACING -0.5


void pen_text_at(context* c, char* text, float x, float y, float pixel_ligne_height)
{
    int offset_x = 0; int offset_y = 0;
    float step = pixel_ligne_height/LETTER_HEIGHT* LETTER_WIDTH;
    int text_length = (int)strlen(text);
    for (int i = 0; i < text_length; i++)
    {
        char letter = text[i];
        if (letter == '\n')
        {
            offset_x = 0;
            offset_y += (1+INTERLIGNE) * LETTER_HEIGHT;
        }
        else{
            pen_char(c, letter, rectanglef(x+offset_x, y+offset_y, 
                                        pixel_ligne_height,
                                        step));
            offset_x += step + step * LETTER_SPACING;
        }
    }
}

void pen_text_at_center(context* c, char* text, float x, float y, float pixel_ligne_height, float centerX, float centerY)
{
    int h = pixel_ligne_height; 
    int step = pixel_ligne_height/LETTER_HEIGHT* LETTER_WIDTH;
    int w = (int)strlen(text) * (step + step * LETTER_SPACING);

    w *= centerX;
    h *= centerY;

    pen_text_at(c, text, x-w, y-h, pixel_ligne_height);
}

void pen_char_at(context* c, char letter, float x, float y, float pixel_ligne_height)
{
    if (letter > ' ' && letter != '\\')
    {
        rect mask = rectangle((letter % NUM_COL_LETTER) * LETTER_WIDTH,
                              ((letter / NUM_COL_LETTER)) * LETTER_HEIGHT,
                              LETTER_WIDTH, LETTER_HEIGHT);
        pen_texture_at(c, c->_pen_font, mask, x, y,
                        pixel_ligne_height/LETTER_WIDTH,
                        pixel_ligne_height/LETTER_HEIGHT);
    }
}

void pen_char(context* c, char letter, rectf dest)
{
    if (letter > ' ' && letter != '\\')
    {
        rect mask = rectangle((letter % NUM_COL_LETTER) * LETTER_WIDTH,
                              ((letter / NUM_COL_LETTER)) * LETTER_HEIGHT,
                              LETTER_WIDTH, LETTER_HEIGHT);
        pen_texture(c, c->_pen_font, mask, dest);
    }
}

bool pen_load(context* c)
{
    c->_pen_font = texture_create(c, "asset/font_amstrad_cpc_18.png");
    pen_mode(c, PEN_MODE_FILL);
    /*
    c->pen_x = 0;
    c->pen_y = 0;
    c->pen_scale = 1;
    c->pen_mode  = 2;
    c->pen_move_rotation = from_degree(0);
    c->_pen_is_down = false;

    repeat(i, 3)
    {
        c->_pen_vertex[i].tex_coord.x = 0;
        c->_pen_vertex[i].tex_coord.y = 0;
    }*/

    return true;
}

void pen_unload(context* c)
{
    texture_free(c->_pen_font);
}

// graph -> windows pixel
float pen_get_graph_pos_x(float pos, graph* g)
{
    return (pos-g->x_min)/g->x_etendu * g->draw_dest.w + g->draw_dest.x;
}

// graph -> windows pixel
float pen_get_graph_pos_y(float pos, graph* g)
{
    return (pos-g->y_min)/g->y_etendu * g->draw_dest.h + g->draw_dest.y;
}

void pen_graph(context* c, graph* g)
{
    /*
    camera_state cs = camera_get_state(c);
    c->camera_x -= posX;
    c->camera_y -= posY;
    //todo le centre à l'écran
    c->camera_scale_x *= height_pixel;
    c->camera_scale_y *= height_pixel;*/

    repeat(i, graph_get_nb_node(g))
    {
        pen_node(c, g, i);

        for(int k = 0; k < graph_node_get_nb_neighbors(g,i); k++)
        {
            int j = graph_get_node_neighbors(g,i,k);
            if(j < i)
            {
                pen_join(c, g, i, j);
            }
        }
    }

    //camera_set_state(c, cs);
}

void pen_node (context* c, graph* g, int i)
{
    pen_color(c, color_black);
    float radius = c->screen_height/64.0;
    float x = pen_get_graph_pos_x(graph_node_x(g,i), g);
    float y = pen_get_graph_pos_y(graph_node_y(g,i), g);
    pen_oval(c, x, y, radius/c->camera_scale_x, radius/c->camera_scale_y);
}

void pen_join (context* c, graph* g, int a, int b)
{
    pen_color(c, color_black);
    float x1 = pen_get_graph_pos_x(graph_node_x(g,a), g);
    float y1 = pen_get_graph_pos_y(graph_node_y(g,a), g);
    float x2 = pen_get_graph_pos_x(graph_node_x(g,b), g);
    float y2 = pen_get_graph_pos_y(graph_node_y(g,b), g);
    pen_line(c,x1, y1, x2, y2);
}