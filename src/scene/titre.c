#include "base.h"

typedef struct 
{
   int nbFoisPresser;
}state;

void scene_titre_load(argument arg)
{
    obtenir_state;
    sce->state = s;

    //sce->info.background_color = rgb(127, 255, 0);
    //sce->info.background_color = rgb(99,   0, 145);
    //sce->info.background_color = rgb(107,   51, 135);

    s->nbFoisPresser = 0;
}

void scene_titre_unload(argument arg) { obtenir_state; }
void scene_titre_update(argument arg) { obtenir_state; }

void scene_titre_draw(argument arg)
{
    obtenir_state;
    pen_graph(c, gs->g);

    // Cancel camera zoom
    camera_state cs = camera_get_state(c);
    camera_set_state(c, camera_state_default());
    // Not affected by scrolling or scalling
    
    pen_formatted_text_at_center(c, 0, 0, FONT_SIZE_NORMAL, 0, 0, "Titre (G: %i nodes)", gs->nb_node);
    pen_formatted_text_at_center(c, 0, FONT_SIZE_NORMAL, FONT_SIZE_NORMAL, 0, 0, "(FDRJHPM)", gs->nb_node);
    camera_set_state(c, cs);
    //pen_circle(c, window_width(c)/2, window_height(c)/2, window_height(c)/32.0 * (s->nbFoisPresser+2));
    //pen_formatted_text_at_center(c, window_width(c)/2,window_height(c)/2, FONT_SIZE_NORMAL, 0.5, 0.5, "UwU tick: %i", c->timer);
}

bool scene_titre_event (argument arg) 
{ 
    obtenir_state;
    return false;
}

void scene_titre_printf(argument arg)
{
    obtenir_state;
    printf("Nb presser = %i\n", s->nbFoisPresser);
}