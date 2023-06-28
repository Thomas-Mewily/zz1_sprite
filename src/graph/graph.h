#ifndef GRAPH_H
#define GRAPH_H
#include "base.h"

#define node_depart 0
#define node_deja_visiter 1
#define node_a_visiter 2

typedef int node_type;

struct graph;

typedef struct
{
    bool exist;
    int idx;
    node_type etat;
    float x;
    float y;
    vec* /*int*/ neightbors;
    bool colorer_en_noir; // Cache pour savoir si on est déjà passer sur le noeud 
} node;
typedef struct
{
    bool exist;
    int a;
    int b;
    float distance;
} join;

struct graph
{
    int    _nb; // nb nodes et joins
    node*  _nodes;  
    join** _joins;
};
typedef struct graph graph; 

graph* graph_empty();
void   graph_free(graph*g);
int graph_add_node_x_y(graph* g, float x, float y);

void node_init(graph* g, int idx);
void join_init(join* j, int a, int b);


void graph_check_index(graph* g, int idx);
int graph_node_get_nb_neighbors(graph* g, int idx);
int graph_get_nb_node(graph* g);

node* graph_get_node(graph* g , int idx);
join* graph_get_join(graph*g, int a, int b);

vec* graph_node_get_neighbors_vec(graph*g , int _joins);
int graph_get_node_neighbors(graph* g, int idx, int neighbors_idx);

bool graph_join_exist(graph*g, int a, int b);
bool graph_node_exist(graph*g, int idx);

void graph_add_join(graph*g , int a, int b);

float graph_node_x(graph * g , int idx);
float graph_node_y(graph * g , int idx);

int graph_nb_node_exist(graph * g);
int graph_nb_join_exist(graph * g);

void graph_node_colorier_blanc(graph * g, int idx);
void graph_node_colorier_noir (graph * g, int idx);
void graph_colorier_nodes_blanc(graph * g);

bool graph_node_en_blanc(graph* g, int idx);
bool graph_node_en_noir (graph* g, int idx);

void graph_printf(graph* g);

graph* graph_complet(int nb_noeud, float radius);

#endif