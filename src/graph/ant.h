#ifndef GRAPH_FOURMI_H
#define GRAPH_FOURMI_H
#include "base.h"

/*
#define ANT_WALK 0
#define ANT_WAIT 1
#define ANT_STOP 2
typedef int ant_state;*/

typedef struct 
{
    // display position on screen
    float x;
    float y;
    angle direction; // Il existe une fonction angle_from_vector(x,y) -> angle

    // Si node_source_idx == node_destination_idx, la fourni ne bouge plus
    int node_source_idx;
    int node_destination_idx;
    graph* g;
    vec* /* de int*/ chemin_a_parcourir;
    int node_source_idy;
    int node_destination_idy;
    //ant_state state;
} ant;

void ant_init(ant* a);

float ant_source_x(ant* a);
float ant_source_y(ant* a);
float ant_destination_x(ant* a);
float ant_destination_y(ant* a);

void ant_update(time delta_time, ant* a);
void ant_display(context* t, ant* a);
