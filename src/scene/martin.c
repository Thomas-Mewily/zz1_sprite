#include "base.h"

typedef struct 
{
   float hue;
   float color_change_speed;
   texture* steve;
   //graph* graph_test;
} state;

void set_bg_color(argument arg)
{
    obtenir_state;
    sce->info.background_color = hsv(s->hue, 0.4, 0.95);
}

void scene_martin_load(argument arg)
{   
    obtenir_state;

    s->hue = 0;
    s->color_change_speed = 0.7;
    set_bg_color(arg);
    s->steve = texture_create(c, "asset/steve.png");

    int nb_node = 10;
    //s->graph_test = graph_generate(nb_node, rectanglef(0, 0, window_width(c), window_height(c)), 0.2);

    vec* path = graph_recuit_simule(gs->g, 0.5, &t_ud_geometric, 100);
    vec_free_lazy( gs->path_rs);
    gs->path_rs = path;
    vec_printf_int(path);
}

void scene_martin_unload(argument arg)
{
    obtenir_state;
    texture_free(s->steve);
    
    // rip la mémoire occuper par froggyS et froggyAnim
    // n'inclue pas froggyAnim dans cette affaire, il est innocent...
}

void scene_martin_update(argument arg)
{
    obtenir_state;
    set_bg_color(arg);
    s->hue += s->color_change_speed;
    if (s->hue >= 360) {s->hue = 0;}

    //camera_set_x(c, window_width(c)/2-input_mouse_x(c)/2);
    //camera_set_y(c, window_width(c)/2-input_mouse_y(c)/2);

    

}
void scene_martin_draw(argument arg)
{
    obtenir_state;
    //pen_circle(c, 100, 100, 50 );
    // pen_text_at(c, "QUOI? azertyuiopqsdfgjhklwxcvbnvc", 0, 0, FONT_SIZE_FULLSCREEN);
    // pen_text_at(c, "QUOI? azertyuiopqsdfgjhklwxcvbnvc", 0, 50, FONT_SIZE_BIG);
    // pen_text_at(c, "QUOI? azertyuiopqsdfgjhklwxcvbnvc", 0, 100, FONT_SIZE_NORMAL);
    // pen_text_at(c, "QUOI? azertyuiopqsdfgjhklwxcvbnvc", 0, 200, FONT_SIZE_SMALL);
    // pen_rect(c, rectanglef(400, 20, 100,20));
    // pen_texture_at(c, s->steve, texture_rect(s->steve), 400, 300, 1, 1);
    // pen_animation_at(c, s->froggyAnim, 10, 400, 3, 3, c->timer);

    pen_graph(c, gs->g);
    pen_draw_trajet(c, gs->g, gs->path_rs);

}

bool scene_martin_event (argument arg) { obtenir_state; return false; }
void scene_martin_printf(argument arg) { obtenir_state; }