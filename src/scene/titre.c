#include "base.h"

#define obtenir_state scene_titre_state* s = (scene_titre_state*)(sce->state);

typedef struct 
{
   int nbFoisPresser;
}scene_titre_state;

void scene_titre_load(context* c, scene* sce)
{
    sce->state = (void*)create(scene_titre_state);
    obtenir_state;
    sce->state = s;

    sce->info.background_color = rgb(127, 255, 0);

    s->nbFoisPresser = 0;
}

void scene_titre_unload(context* c, scene* sce)
{
    free(sce->state);
}


void scene_titre_update(context* c, scene* sce)
{
    obtenir_state;

    //if (pull_up_masked(c->mouse_flag, c->mouse_old_flag, SDL_BUTTON(1) & SDL_BUTTON(2)))
    if (c->mouse_flag & (SDL_BUTTON(1) & SDL_BUTTON(2)))
    {
        s->nbFoisPresser++;
        if(s->nbFoisPresser >= 20)
        {
            c->should_exit = true;
        }
    }
    if (c->kb_state[SDL_SCANCODE_M])
    {
        scene_set(c, martin);
    }
    else if (c->kb_state[SDL_SCANCODE_T])
    {
        scene_set(c, thomas_parallax);
    }
}

void scene_titre_draw(context* c, scene* sce)
{
    obtenir_state;
    pen_circle(c, c->window_width/2, c->window_height/2, c->window_height/32.0 * (s->nbFoisPresser+2));
}

void scene_titre_printf(context* c, scene* sce)
{
    obtenir_state;
    printf("Nb presser = %i\n", s->nbFoisPresser);
}

#undef obtenir_state