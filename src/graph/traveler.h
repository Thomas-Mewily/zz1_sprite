#ifndef GRAPH_TRAVELER_H
#define GRAPH_TRAVELER_H
#include "base.h"

/*
#define traveler_WALK 0
#define traveler_WAIT 1
#define traveler_STOP 2
typedef int traveler_state;*/

typedef int traveler_end_action;
typedef int traveler_state;
typedef int traveler_node_action;

#define TRAVELER_END_STOP 0
#define TRAVELER_END_LOOP 1

#define TRAVELER_STATE_WAIT 0
#define TRAVELER_STATE_WALK 1
#define TRAVELER_STATE_WAIT_TO_WALK 2

#define TRAVELER_NODE_ACTION_NOTHINGS      0
#define TRAVELER_NODE_ACTION_SET_COLLECTED 1

int trajet_length(trajet* t);
void trajet_add_node(trajet* t, int node_des);
int trajet_get(trajet* t, int idx);
trajet* trajet_empty();
bool trajet_is_empty(trajet* t);

typedef struct 
{
    // display position on screen
    float x;
    float y;
    angle direction; // Il existe une fonction angle_from_vector(x,y) -> angle

    // Si node_source_idx == node_destination_idx, la fourni ne bouge plus
    time source_begin;
    time last_time_updated;
    float distance_per_second;
    int source_idx;

    float total_distance_traveled;
    float old_total_distance_traveled;

    graph* g;
    trajet* chemin;
    traveler_end_action reach_end_action;
    traveler_state state;
    traveler_node_action node_action;
} traveler;

traveler* traveler_create(graph* g, float distance_per_second);
void traveler_free(traveler* t);
// perdu, aucune traversé
bool traveler_is_nowhere(traveler* t); 
void traveler_travel_node(traveler* t, int idx);
void traveler_add_travel(traveler* t, trajet* tr_will_be_copied);
void traveler_set_travel(traveler* t, trajet* tr_will_be_copied);
bool traveler_can_travel(traveler* t);

float traveler_source_x(traveler* t);
float traveler_source_y(traveler* t);
float traveler_destination_x(traveler* t);
float traveler_destination_y(traveler* t);

float traveler_distance_to_reach_next_node(traveler* t);
float traveler_distance_already_traveled_to_reach_next_node(context* c, traveler* t);

// t est dans [0, 1]
float traveler_get_time_coef(context* c, traveler* t);

void traveler_update(context* c, traveler* t);
time traveler_time(traveler* t);
#endif