#include "base.h"

typedef struct 
{
   float hue;
   float color_change_speed;
   texture* steve;
//    sprite_sheet* froggyS;
//    anim* froggyAnim;
   graph* graph_test;
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
    // s->froggyS = sprite_sheet_create(c, "asset/froggyChair.png", 54, 54);
    // s->froggyAnim = animation_create(s->froggyS, frequence_s(20));

    int nb_node = 30;
    s->graph_test = graph_gen_nul_equi(nb_node, rectanglef(40, 40, window_width(c), window_height(c)));
    graph_link_arbre_couvrant(s->graph_test);

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

    graph* g = s->graph_test;
    int offset_x = 0;
    int offset_y = 0;
    float radius = 5;
    float scale = 1;
    pen_color(c,rgb(0,0,0));
    repeat(i, graph_get_nb_node(g))
    {

        float x = graph_node_x(g,i);
        float y =graph_node_y(g,i);
        pen_circle(c,scale*x +offset_x,scale*y+offset_y, radius);
        //SDL_Log("noeud n°%d, x = %F; y = %f", i, x, y);
        
        for(int k = 0; k < graph_node_get_nb_neighbors(g,i); k++)
        {
            int j = graph_get_node_neighbors(g,i,k);
            float xj = graph_node_x(g,j);
            float yj =graph_node_y(g,j);
            pen_line(c,scale*x +offset_x,scale*y+offset_y,scale*xj +offset_x,scale*yj+offset_y);
        }
    }
}

bool scene_martin_event (argument arg) { obtenir_state; return false; }
void scene_martin_printf(argument arg) { obtenir_state; }