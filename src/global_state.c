#include "base.h"

void global_state_load(context* c)
{
    gs = create(the_global_state);
    gs->g = graph_complet(5, 1);
}

void global_state_unload(context* c)
{
    graph_free(gs->g);
    free(gs);
}