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

#define X(x) camera_cam_pos_2_pixel_pos_x(c, x)
#define Y(y) camera_cam_pos_2_pixel_pos_y(c, y)

rectf apply_offset(context* c, rectf r)
{
    return rectanglef(X(r.x), Y(r.y), r.w*camera_scale_x(c), r.h*camera_scale_y(c));
}

// todo : affected by pen size
void pen_line(context* c, float x1, float y1, float x2, float y2) { pen_pixel_line(c, X(x1), Y(y1), X(x2), Y(y2)); }
void pen_dot(context* c, float x, float y) { pen_pixel(c, X(x), Y(y)); }
void pen_rect(context* c, rectf r) { r = apply_offset(c, r); pen_pixel_rect(c, r); }




void pen_pixel(context* c, float x, float y) { SDL_RenderDrawPointF(renderer, x, y); }
void pen_pixel_line(context* c, float x1, float y1, float x2, float y2) { SDL_RenderDrawLineF(renderer, x1, y1, x2, y2); }
void pen_pixel_rect(context* c, rectf r) 
{ 
    c->pen_nb_rectangle++;
    SDL_RenderFillRectF(renderer, &r);
}

void pen_pixel_oval(context* c, rectf dest)
{

    // ovale off screen
    if(dest.x > window_width(c) || dest.y > window_height(c) || dest.x +dest.w < 0 || dest.y +dest.h < 0) return;
    float radius_x = dest.w/2;
    float radius_y = dest.h/2;
    float x = dest.x+radius_x;
    float y = dest.y+radius_y;
    //printf("%f, %f\n", x, y);

    if((c->pen_mode) & PEN_MODE_FILLED)
    {
        int stepPrecision = 1; // 2 pixel tickness

        float radius_begin; 
        float radius_end; 
        //radius_begin = maxif(0, radius_x-x);
        //radius_end = maxif(0, radius_x+(window_width(c)-x));

        //float rx_max = radius_end;  //radius_x;

        radius_begin  = 0;
        radius_end = radius_x;

        for(float rx = radius_begin; rx < radius_end; rx+=stepPrecision)
        {
            float height = radius_y*sqrt(1-(1-rx/radius_x)*(1-rx/radius_x));
            pen_pixel_rect(c, rectanglef(x-radius_x+rx,y-height, 2*(radius_x - rx), 2*height));
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
                pen_pixel_line(c, x+old_x, y+old_y, x+new_x, y+new_y);
                old_x = new_x;
                old_y = new_y;
            }
        }
    }
}


void pen_circle(context* c, float x, float y, float radius) { pen_oval(c, x, y, radius, radius); }
void pen_oval(context* c, float x, float y, float radius_x, float radius_y)
{
    rectf dest_pixel = apply_offset(c, rectanglef(x-radius_x,y-radius_y,2*radius_x,2*radius_y));
    pen_pixel_oval(c, dest_pixel);
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
    float offset_x = 0; int offset_y = 0;
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


void pen_join_info (context* c, graph* g, int a, int b)
{
    if(a == b) { return; }
    join* j = graph_get_join(g,a,b);
    bool exist = graph_join_exist(g, a, b);

    // node existe pas
    if(exist == false && g->draw_text_info != GRAPH_DISPLAY_MODE_LOT_OF_TEXT) {  return; }

    float xa = camera_graph_pos_2_cam_pos_x(c, g, graph_node_x(g,a));
    float ya = camera_graph_pos_2_cam_pos_y(c, g, graph_node_y(g,a));
    float xb = camera_graph_pos_2_cam_pos_x(c, g, graph_node_x(g,b));
    float yb = camera_graph_pos_2_cam_pos_y(c, g, graph_node_y(g,b));

    if(g->draw_text_info == GRAPH_DISPLAY_MODE_LOT_OF_TEXT || g->draw_text_info == GRAPH_DISPLAY_MODE_GRAPHIC || g->draw_text_info == GRAPH_DISPLAY_MODE_MINIMAL_TEXT)
    {
        bool big_graph = graph_get_nb_node(g) >= 17;
        int node_not_pressed = -1;
        if(big_graph)
        {
            if(graph_node_is_touched_by_mouse(c, g, a))
            {
                node_not_pressed = b;
            }else if(graph_node_is_touched_by_mouse(c, g, b))
            {
                node_not_pressed = a;
            }
            if(node_not_pressed == -1) { return; }
        }
        //float txt_x = (x1 + x2)/2;
        //float txt_y = (y1 + y2)/2;
        float font_size = FONT_SIZE_SMALL;
        float txt_y_offset = font_size*0.35;

        float mx = camera_pixel_pos_2_cam_pos_x(c, input_mouse_x(c));
        float my = camera_pixel_pos_2_cam_pos_y(c, input_mouse_y(c));

        //float diag = (g->x_etendu*g->y_etendu);
        //float coef1 = 1 + diag/(length(x1, y1, mx, my)+0.1*diag);
        //float coef2 = 1 + diag/(length(x2, y2, mx, my)+0.1*diag);
        
        float avg = length(xa, ya, xb, yb);

        float coefa = avg/2 + length(xb, yb, mx, my);
        float coefb = avg/2 + length(xa, ya, mx, my);

        if(big_graph)
        {
            coefa = 0.3;
            coefb = 0.3;
            if (node_not_pressed == a)
            {
                coefa = 1;
            }else{ coefb = 1; }
        }

        //coef1 = 1;
        //coef2 = 1;


        float txt_x = (xa * coefa + xb * coefb) / ( coefa + coefb);
        float txt_y = (ya * coefa + yb * coefb) / ( coefa + coefb);

        pen_formatted_text_at_center(c, txt_x, txt_y-txt_y_offset, font_size, 0.5, 0.5, "%.1f",  graph_get_join(g, a, b)->distance);

        if(g->draw_text_info == GRAPH_DISPLAY_MODE_LOT_OF_TEXT)
        {
            pen_formatted_text_at_center(c, txt_x, txt_y+txt_y_offset, font_size, 0.5, 0.5, "b%.1f",  graph_join_get_distance_opti(g, a, b));
            pen_formatted_text_at_center(c, txt_x, txt_y+3*txt_y_offset, font_size, 0.5, 0.5, "f%.4f",  j->testosterone);
        }
    }
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

    if(g->draw_text_info == GRAPH_DISPLAY_MODE_LOT_OF_TEXT)
    {
        repeat(i, graph_get_nb_node(g))
        {
            repeat(j, i)
            {   
                pen_join(c, g, i, j);
            }
        }

        repeat(i, graph_get_nb_node(g))
        {

            repeat(j, i)
            {   
                pen_join_info(c, g, i, j);
            }
        }
    }else
    {
        repeat(i, graph_get_nb_node(g))
        {
            for(int k = 0; k < graph_node_get_nb_neighbors(g, i); k++)
            {
                int j = graph_get_node_neighbors(g,i,k);
                pen_join(c, g, i, j);
            }
        }

        repeat(i, graph_get_nb_node(g))
        {
            for(int k = 0; k < graph_node_get_nb_neighbors(g, i); k++)
            {   
                int j = graph_get_node_neighbors(g,i,k);
                pen_join_info(c, g, i, j);
            }
        }
    }

    repeat(i, graph_get_nb_node(g))
    {
        pen_node(c, g, i);
    }

    //camera_set_state(c, cs);
}

void pen_node (context* c, graph* g, int i)
{
    float radius = NODE_RADIUS_PIXEL;
    node* n = graph_get_node(g, i);
    float x = camera_graph_pos_2_cam_pos_x(c, g, graph_node_x(g,i));
    float y = camera_graph_pos_2_cam_pos_y(c, g, graph_node_y(g,i));

    pen_color(c, color_black);
    pen_oval(c, x, y, radius/c->camera_scale_x, radius/c->camera_scale_y);

    color co = rgb(192,192,192);
    if(graph_node_is_touched_by_mouse(c,g,i))
    {
        co = color_white;
    }
    pen_color(c, co);

    radius *= 0.75;
    pen_oval(c, x, y, radius/c->camera_scale_x, radius/c->camera_scale_y);
    //pen_rect(c, rectanglef(x-radius/c->camera_scale_x/2, y-radius/c->camera_scale_y/2, radius/c->camera_scale_x, radius/c->camera_scale_y));

    switch (g->draw_text_info)
    {
        case GRAPH_DISPLAY_MODE_MINIMAL_TEXT:
        case GRAPH_DISPLAY_MODE_MINIMAL_TEXT_COLORED:
        case GRAPH_DISPLAY_MODE_LOT_OF_TEXT:
        {
            float txt_x = x;
            float txt_y = y;
            //pen_formatted_text_at_center(c, txt_x, txt_y, FONT_SIZE_NORMAL, 0.5, 1, "#%i order%i",  n->idx, n->order);
            pen_formatted_text_at_center(c, txt_x, txt_y, FONT_SIZE_NORMAL, 0.5, 1, "%i",  n->idx);
        }
        break;
    
        case GRAPH_DISPLAY_MODE_GRAPHIC:
        {
            if(n->etat == node_a_visiter)
            {
                float scale = 4;
                pen_animation_at_center(c, gs->diamant_anim, x, y, scale, scale, 0.5, 0.5, timer_since_launch(c));
            }
        }
        break;
        default: break;
            
    }
}


void pen_join (context* c, graph* g, int a, int b)
{
    if(a == b) { return; }
    join* j = graph_get_join(g,a,b);
    bool exist = graph_join_exist(g, a, b);

    // node existe pas
    if(exist == false && g->draw_text_info != GRAPH_DISPLAY_MODE_LOT_OF_TEXT) {  return; }

    color co = color_black;
    if(g->draw_text_info == GRAPH_DISPLAY_MODE_LOT_OF_TEXT || g->draw_text_info == GRAPH_DISPLAY_MODE_MINIMAL_TEXT_COLORED)
    {
        if(exist == false){ co = rgba(0,255,0,0); }
        else if(graph_join_get_distance_opti(g, a, b) < j->distance)
        {
            co = color_red;
        }
    }
    pen_color(c, co);
    
    float xa = camera_graph_pos_2_cam_pos_x(c, g, graph_node_x(g,a));
    float ya = camera_graph_pos_2_cam_pos_y(c, g, graph_node_y(g,a));
    float xb = camera_graph_pos_2_cam_pos_x(c, g, graph_node_x(g,b));
    float yb = camera_graph_pos_2_cam_pos_y(c, g, graph_node_y(g,b));

    pen_line(c,xa, ya, xb, yb);
}


void pen_line_in_graph(context* c, graph* g, float x1, float y1, float x2, float y2)
{
    x1 = camera_graph_pos_2_cam_pos_x(c, g, x1);
    y1 = camera_graph_pos_2_cam_pos_y(c, g, y1);
    x2 = camera_graph_pos_2_cam_pos_x(c, g, x2);
    y2 = camera_graph_pos_2_cam_pos_y(c, g, y2);

    pen_line(c, x1, y1, x2, y2);
}

// inside graph
void pen_draw_arrow(context* c, graph* g, float x, float y, angle a)
{
    angle a2 = from_degree(135);
    float radius = 0.1 * NODE_RADIUS_PIXEL;// / camera_scale_x(c);
    pen_line_in_graph(c, g, x, y, x+cos(a-a2)*radius, y+sin(a-a2)*radius);
    pen_line_in_graph(c, g, x, y, x+cos(a+a2)*radius, y+sin(a+a2)*radius);
}

float pen_draw_join_direction(context* c, graph* g, int a, int b)
{
    join* j = graph_get_join(g, a, b);
    if(j == null) return 0;


    float x1 = graph_node_x(g, a);
    float y1 = graph_node_y(g, a);

    float x2 = graph_node_x(g, b);
    float y2 = graph_node_y(g, b);

    float dx = x2-x1;
    float dy = y2-y1;

    float l1 = j->distance;
    float l2  = length(x1, y1, x2, y2);

    float slow = l2/l1;

    angle ang = angle_from_vector(dx, dy);

    //float speed = g->rectangle_length / 32.0;
    float step = 1/5.0f;

    for(float i = mod(second(timer_scene(c)*slow), step); i < 1; i += step)
    {
        pen_draw_arrow(c, g, x1+dx*i, y1+dy*i, ang);
    }

    pen_line_in_graph(c, g, x1, y1, x2, y2);

    return l1 / g->rectangle_length;
}

float _pen_draw_trajet(context* c, graph* g, trajet* t, float hue)
{
    if(t == null || trajet_length(t) <= 1) return hue;

    for(int i = 0; i<trajet_length(t)-1; i++)
    {
        pen_color(c, hsv(mod(hue, 360), 1, 0.65));
        pen_draw_join_direction(c, g, trajet_get(t, i), trajet_get(t, i+1));
        hue += 360/8.0f;
        //hue += 140.0f;
    }
    return hue;
}

void pen_draw_trajet(context* c, graph* g, trajet* t)
{
    _pen_draw_trajet(c, g, t, 140);
}



void pen_draw_trajet_full(context* c, graph* g, trajet* t)
{
    if(t == null || trajet_length(t) <= 1) return;

    float hue = 140;
    for(int i = 0; i < trajet_length(t)-1; i++)
    {
        hue = _pen_draw_trajet(c, g, graph_get_join(g, trajet_get(t, i), trajet_get(t, i+1))->distance_opti_node_a_passer, hue);
    }
}