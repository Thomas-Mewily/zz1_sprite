#include "base.h"

typedef struct 
{
   int dummy;
}state;

void scene_graph_joueur_load(argument arg)
{
    obtenir_state;
    global_state_reset_traveler(c);
}

void scene_graph_joueur_unload(argument arg) { obtenir_state; }
void scene_graph_joueur_update(argument arg) 
{ 
    obtenir_state;
    traveler_update(c, gs->goblin_traveler);    
}

int direction_to_gobelin_animation(angle a)
{
    // bidouille
    float x = cos(a);
    float y = sin(a);
    if(abs(x) > abs(y))
    {
        if(x > 0) return 2;
        return 3;
    }
    if(y > 0) return 0;
    return 1;
}

void scene_graph_joueur_draw(argument arg)
{
    obtenir_state;
    pen_graph(c, gs->g);

    if(gs->g->draw_text_info == GRAPH_DISPLAY_MODE_GRAPHIC)
    {
        pen_draw_trajet(c, gs->g, gs->goblin_traveler->chemin);

        graph* g = gs->g;
        traveler* t = gs->goblin_traveler;

        int is_base_anim = t->state == TRAVELER_STATE_WAIT_TO_WALK;
        int nb_frame = is_base_anim ? 2 : 4;
        int frame_fps = is_base_anim ? 3 : 8;
        int direction = direction_to_gobelin_animation(t->direction);


        rect src = rectangle(traveler_time(t) / (frequence_s(frame_fps)) % nb_frame * 24,
                        (4*(is_base_anim?0:1)+direction)*32,24,32);
        pen_texture_at_center(c, gs->gobelin_texture, src, camera_graph2cam_x(c,g,t->x), camera_graph2cam_y(c,g,t->y), 3, 3, 0.5, 0.5);
    
        // Cancel camera zoom
        camera_state cs = camera_get_state(c);
        camera_set_state(c, camera_state_default());
        // Not affected by scrolling or scalling
        pen_formatted_text_at_center(c, 0, 0, FONT_SIZE_NORMAL, 0, 0, "Temps : %.1f", gs->goblin_traveler->total_distance_traveled);
        camera_set_state(c, cs);
    }

    //pen_circle(c, window_width(c)/2, window_height(c)/2, window_height(c)/32.0 * (s->nbFoisPresser+2));
    //pen_formatted_text_at_center(c, window_width(c)/2,window_height(c)/2, FONT_SIZE_NORMAL, 0.5, 0.5, "UwU tick: %i", c->timer);
}

bool scene_graph_joueur_event (argument arg) 
{ 
    obtenir_state;

    switch (ev->type)
    {
        case SDL_MOUSEBUTTONDOWN:
        {
            node* n = graph_get_node_touched_by_mouse(c, gs->g);
            if(n != null)
            {
                traveler_travel_node(gs->goblin_traveler, n->idx);
            }
            return true;
        }   
        break;
        default: break;
    }

    return false;
}

void scene_graph_joueur_printf(argument arg)
{
    obtenir_state;
    printf("In game baby = \n");
}