#include "base.h"

void global_state_load(context* c)
{
    gs = create(the_global_state);
    gs->g = graph_complet(4);
}

void global_state_unload(context* c)
{
    graph_free(gs->g);
    free(gs);
}

void global_state_update(context* c)
{
    gs->g->draw_dest = window_rectf(c);
}
void global_state_draw(context* c)
{
    pen_graph(c, gs->g);
}


bool global_state_event(context* c, event* ev)
{
    switch (ev->type)
    {
        case SDL_KEYDOWN:
        {
            switch (ev->key.keysym.sym)
            {
                case SDLK_d: gs->g->draw_text_info = !gs->g->draw_text_info; break;
                default: break;
            }
        } break;
        default: break;
    }

    return false;
}