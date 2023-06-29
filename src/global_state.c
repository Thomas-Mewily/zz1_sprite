#include "base.h"

void global_state_load(context* c)
{
    gs = create(the_global_state);

    //gs->g = graph_complet(6, 1);
    gs->g = graph_generate(5, rectanglef(40, 40, window_width(c), window_height(c)), 0.2);

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
