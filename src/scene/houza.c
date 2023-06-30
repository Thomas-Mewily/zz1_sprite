#include "base.h"
#include <stdlib.h>

typedef struct 
{
    int dummy;
   //texture* steve;
   //graph* g;
  
} state;

void scene_houza_load(argument arg)
{
    obtenir_state;
 
    //s->g = graph_complet(20);
    //s->a = ant_create(s->a);

    sce->info.background_color = rgb(0,0,0);
    //graph_printf(s->g);
    //s->steve = texture_create(c, "asset/Steve.png");
    debug;

    int nb_node = 10;
    if(gs->g)
    {
        graph_free(gs->g);
    }
    gs->g = graph_generate(nb_node, rectanglef(0,0, window_width(c), window_height(c)), 0.2);

}


void scene_houza_unload(argument arg)
{
    obtenir_state;

    //graph_free(gs->g);

    
   // texture_free(s->steve);
}

void scene_houza_update(argument arg)
{
    obtenir_state;
    //ant_update(10,s->a);

    if(c->kb_state[SDL_SCANCODE_N])
    {
        scene_set(c,thomas_parallax);
    }
} 

void scene_houza_draw(argument arg)
{
    obtenir_state;
    pen_graph(c, gs->g);
}

bool scene_houza_event (argument arg) { obtenir_state; return false; }
void scene_houza_printf(argument arg)
{
    obtenir_state;
    printf("Parallax de houza\n");
}