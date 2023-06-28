#include "base.h"

typedef struct 
{
   int nbFoisPresser;
}state;

void scene_titre_load(argument arg)
{
    obtenir_state;
    sce->state = s;

    sce->info.background_color = rgb(127, 255, 0);

    s->nbFoisPresser = 0;
}

void scene_titre_unload(argument arg) { obtenir_state; }
void scene_titre_update(argument arg) { obtenir_state; }

void scene_titre_draw(argument arg)
{
    obtenir_state;
    pen_circle(c, c->window_width/2, c->window_height/2, c->window_height/32.0 * (s->nbFoisPresser+2));
    //pen_text_at(c, "UwU", 0,0, FONT_SIZE_FULLSCREEN);
    //pen_text_at_center(c, "UwU", c->window_width/2,c->window_height/2, FONT_SIZE_NORMAL, 0.5, 0.5);

    pen_formatted_text_at_center(c, c->window_width/2,c->window_height/2, FONT_SIZE_NORMAL, 0.5, 0.5, "UwU tick: %i", c->timer);
}

bool scene_titre_event (argument arg) 
{ 
    obtenir_state;

    switch (ev->type)
    {
        //mousePress(ev->button.);
        case SDL_MOUSEBUTTONDOWN: s->nbFoisPresser++; break;
        case SDL_KEYDOWN: case SDL_KEYUP:
        {
            switch (ev->key.keysym.sym)
            {
                case SDLK_ESCAPE: c->should_exit = true; break;
                case SDLK_m: scene_set(c, martin); return true;
                case SDLK_t: scene_set(c, thomas_parallax); return true;
                case SDLK_h: scene_set(c, houza); return true;
                default: break;
            }
        } break;
        default: break;
    }
    return false;
}

void scene_titre_printf(argument arg)
{
    obtenir_state;
    printf("Nb presser = %i\n", s->nbFoisPresser);
}

#undef obtenir_state