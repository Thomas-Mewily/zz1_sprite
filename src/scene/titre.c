#include "base.h"

typedef struct 
{
   int nbFoisPresser;
   int node_hold;
}state;

void scene_titre_load(argument arg)
{
    obtenir_state;
    s->node_hold = -1;
    //sce->info.background_color = rgb(127, 255, 0);
    //sce->info.background_color = rgb(99,   0, 145);
    //sce->info.background_color = rgb(107,   51, 135);

    s->nbFoisPresser = 0;
}

void scene_titre_unload(argument arg) 
{ 
    obtenir_state;
    camera_allow_scrolling(c, true);
    camera_allow_zoom(c, true);
    
    if(graph_get_nb_node(gs->g) >= 1)
    {
        graph_set_node_x_y(gs->g, 0, graph_node_x(gs->g, 0), graph_node_y(gs->g, 0));
    }
}

void scene_titre_update(argument arg) 
{ 
    obtenir_state;

    if(s->node_hold != -1)
    {
        graph* g = gs->g;
        float x = graph_node_x(g, s->node_hold);
        x+=input_mouse_delta_x(c) / g->x_etendu/camera_scale_x(c);
        float y = graph_node_y(g, s->node_hold);
        y+=input_mouse_delta_y(c) / g->y_etendu/camera_scale_y(c);
        node* n = graph_get_node(g, s->node_hold);


        graph_set_node_x_y(gs->g, n->idx, x, y);
        //n->x = x;
        //n->y = y;
    }
}

void scene_titre_draw(argument arg)
{
    obtenir_state;
    pen_graph(c, gs->g);

    // Cancel camera zoom
    camera_state cs = camera_get_state(c);
    camera_set_state(c, camera_state_default());
    // Not affected by scrolling or scalling
    
    pen_formatted_text_at_center(c, 0, 0, FONT_SIZE_NORMAL, 0, 0, "Titre (G: %i nodes)", gs->nb_node);
    pen_text_at_center(c, "(FDRJHPM)", 0, FONT_SIZE_NORMAL, FONT_SIZE_NORMAL, 0, 0);
    camera_set_state(c, cs);
    //pen_circle(c, window_width(c)/2, window_height(c)/2, window_height(c)/32.0 * (s->nbFoisPresser+2));
    //pen_formatted_text_at_center(c, window_width(c)/2,window_height(c)/2, FONT_SIZE_NORMAL, 0.5, 0.5, "UwU tick: %i", c->timer);
}

bool scene_titre_event (argument arg) 
{ 
    obtenir_state;

    switch (ev->type)
    {
        case SDL_MOUSEBUTTONUP:
        {
            s->node_hold = -1;
            camera_allow_scrolling(c, true);
            camera_allow_zoom(c, true);
        }break;
        case SDL_MOUSEBUTTONDOWN:
        {
            node* n = graph_get_node_touched_by_mouse(c, gs->g);
            if(n != null)
            {
                s->node_hold = n->idx;
                camera_allow_scrolling(c, false);
                camera_allow_zoom(c, false);
            }
            return true;
        }   
        break;
        default: break;
    }

    return false;
}

void scene_titre_printf(argument arg)
{
    obtenir_state;
    printf("Nb presser = %i\n", s->nbFoisPresser);
}