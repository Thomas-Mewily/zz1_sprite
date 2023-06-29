#include "base.h"

void global_state_load(context* c)
{
    gs = create(the_global_state);
    gs->g = graph_empty();
    //gs->g = graph_generate(8, rectanglef(0, 0, 16, 9), 0.25f);

    graph* g = gs->g;
    //gs->g = graph_complet(4);
    
    int a = graph_add_node_x_y(g, 0,  0);
    int b = graph_add_node_x_y(g, 1,  0);
    int x = graph_add_node_x_y(g, 1, -1);
    int y = graph_add_node_x_y(g, 0.7, -2);
    int z = graph_add_node_x_y(g, 1.5, -1.5);
    graph_add_join(g, a, b);
    graph_add_join(g, b, x);
    graph_add_join(g, x, y);
    graph_add_join(g, y, z);
    graph_add_join(g, z, x);
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