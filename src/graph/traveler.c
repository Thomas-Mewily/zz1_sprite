#include "base.h"

int trajet_length(trajet* t) { return t->length; }
int trajet_get(trajet* t, int idx) { return vec_get(t, int, idx); }
trajet* trajet_empty() { return vec_empty(int); }
bool trajet_is_empty(trajet* t) { return t->length == 0; }
void trajet_add_node(trajet* t, int node_des) { vec_push(t, int, node_des); }

#define traveler_timer timer_since_launch(c)

traveler* traveler_create(graph* g, float distance_per_second)
{
    if(g == null) { return null; }
    traveler* t = create(traveler);
    t->x = 0;
    t->y = 0;
    t->g = g;
    t->direction = from_degree(0);
    t->distance_per_second = distance_per_second;
    t->source_begin  = 0;
    t->chemin = trajet_empty();
    t->source_idx = 0;
    t->reach_end_action = TRAVELER_END_STOP;
    t->state = TRAVELER_STATE_WAIT_TO_WALK;
    t->old_total_distance_traveled = 0;
    t->total_distance_traveled = 0;
    t->node_action = TRAVELER_NODE_ACTION_SET_COLLECTED;
    return t;
}
void traveler_free(traveler* t)
{
    if(t == null) return;
    vec_free_lazy(t->chemin);
    free(t);
}

bool traveler_is_nowhere(traveler* t) { return t->chemin == null || trajet_is_empty(t->chemin) || t->source_idx < 0 || t->source_idx >= trajet_length(t->chemin); }
bool traveler_can_travel(traveler* t) 
{
    return (!traveler_is_nowhere(t) && (t->source_idx+1) < trajet_length(t->chemin));
}


void traveler_travel_node(traveler* t, int idx)
{
    if(traveler_is_nowhere(t) || traveler_can_travel(t) == false)
    {
        t->source_idx = t->chemin->length-1;
        if(t->source_idx < 0) { t->source_idx = 0; }
        t->state = TRAVELER_STATE_WAIT_TO_WALK;
    }
    trajet_add_node(t->chemin, idx);
    if(t->chemin->length >= 2)
    {
        join* j = graph_get_join(t->g, trajet_get(t->chemin, trajet_length(t->chemin)-1), trajet_get(t->chemin, trajet_length(t->chemin)-2));
        if(j == null || j->_exist == false || j->distance < 0)
        {
            vec_remove_end(t->chemin);
        }
    }
}
void traveler_add_travel(traveler* t, trajet* tr_will_be_copied)
{
    repeat(i, tr_will_be_copied->length)
    {
        trajet_add_node(t->chemin, trajet_get(tr_will_be_copied, i));
    }
}
void traveler_set_travel(traveler* t, trajet* tr_will_be_copied)
{
    if(tr_will_be_copied == null) { return; }
    if(t->chemin != null) { vec_free_lazy(t->chemin); }
    t->chemin = vec_clone(tr_will_be_copied);
    t->source_idx = 0;
    t->state = TRAVELER_STATE_WAIT_TO_WALK;
}

float traveler_current_delta_x(traveler* t)
{
    return traveler_destination_x(t) - traveler_source_x(t);
}
float traveler_current_delta_y(traveler* t)
{
    return traveler_destination_y(t) - traveler_source_y(t);
}
float traveler_source_x(traveler* t)
{
    if(traveler_is_nowhere(t)) return 0;
    return graph_node_x(t->g, trajet_get(t->chemin,t->source_idx));
}
float traveler_source_y(traveler* t)
{
    if(traveler_is_nowhere(t)) return 0;
    return graph_node_y(t->g, trajet_get(t->chemin,t->source_idx));
}
float traveler_destination_x(traveler* t)
{
    if(!traveler_can_travel(t)) return 0;
    return graph_node_x(t->g, trajet_get(t->chemin, t->source_idx+1));
}
float traveler_destination_y(traveler* t)
{
    if(!traveler_can_travel(t)) return 0;
    return graph_node_y(t->g, trajet_get(t->chemin, t->source_idx+1));
}

float traveler_distance_to_reach_next_node(traveler* t)
{
    if(!traveler_can_travel(t)) return 0;
    int a = trajet_get(t->chemin, t->source_idx);
    int b = trajet_get(t->chemin, t->source_idx+1);
    if(a == b) return 0;
    return graph_get_join(t->g, a, b)->distance;
}

float traveler_get_time_coef(context* c, traveler* t)
{
    if(!traveler_can_travel(t)) return 0;
    time since_begin = traveler_timer-t->source_begin;
    float distance_parcouru = t->distance_per_second * second(since_begin);
    return distance_parcouru / traveler_distance_to_reach_next_node(t);
}

float traveler_distance_already_traveled_to_reach_next_node(context* c, traveler* t)
{
    if(!traveler_can_travel(t)) return 0;
    time since_begin = traveler_timer-t->source_begin;
    float distance_parcouru = t->distance_per_second * since_begin;
    return distance_parcouru;
}

void traveler_set_state(context* c, traveler* t, traveler_state st)
{
    t->source_begin = traveler_timer;
    t->state = st;
}
    
void start_traveling_to_node(context* c, traveler* t)
{
    traveler_set_state(c, t, TRAVELER_STATE_WALK);
}


time traveler_time(traveler* t)
{
    return t->last_time_updated-t->source_begin;
}

void traveler_reach_node(context* c, traveler* t, int idx)
{
    UNUSED(c);
    if(t->node_action == TRAVELER_NODE_ACTION_SET_COLLECTED)
    {
        graph_get_node(t->g, idx)->etat = node_deja_visiter;
    }
}


void traveler_update(context* c, traveler* t)
{
    t->last_time_updated = traveler_timer;
    if(t->state == TRAVELER_STATE_WAIT) return;
    if(traveler_is_nowhere(t)) return;

    t->x = traveler_source_x(t);
    t->y = traveler_source_y(t);

    if(t->state == TRAVELER_STATE_WAIT_TO_WALK)
    {
        if(!traveler_can_travel(t))  return;
        start_traveling_to_node(c, t);
    }

    if(!traveler_can_travel(t)) return;

    float distance = traveler_distance_to_reach_next_node(t);
    float dt = traveler_get_time_coef(c, t);

    t->total_distance_traveled = t->old_total_distance_traveled+dt*distance;

    if(dt < 1)
    {
        float x_add = dt* traveler_current_delta_x(t);
        float y_add = dt* traveler_current_delta_y(t);
        t->x = traveler_source_x(t) +  x_add;
        t->y = traveler_source_y(t) +  y_add;
        t->direction = angle_from_vector(x_add, y_add);
    }else
    {
        t->old_total_distance_traveled += distance;
        t->total_distance_traveled = t->old_total_distance_traveled;
        t->x = traveler_destination_x(t);
        t->y = traveler_destination_y(t);
        traveler_reach_node(c, t, trajet_get(t->chemin, t->source_idx+1));

        t->source_idx++;
        if(traveler_is_nowhere(t))
        {
            t->source_idx--;
        }
        traveler_set_state(c, t, TRAVELER_STATE_WAIT_TO_WALK);
    }
}
