#include "base.h"

#define ant_speex_unit_per_second 100

float ant_source_x(ant* a) { return graph_node_x(a->g, a->node_source_idx); }
float ant_source_y(ant* a) { return graph_node_y(a->g, a->node_source_idx); }
float ant_destination_x(ant* a) { return graph_node_x(a->g, a->node_destination_idx); }
float ant_destination_y(ant* a) { return graph_node_y(a->g, a->node_destination_idx); }

void ant_update(time delta_time, ant* a)
{
    float deplacement = ant_speex_unit_per_second*second(delta_time);
    UNUSED(deplacement);
    UNUSED(a);

    // avance de 
}

void ant_display(context* t, ant* a)
{
    UNUSED(t);
    UNUSED(a);
}

