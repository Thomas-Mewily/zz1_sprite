#ifndef GRAPH_H
#define GRAPH_H
#include "base.h"

#define node_depart 0
#define node_deja_visiter 1
#define node_a_visiter 2

typedef int node_type;

//struct graph;

#define NODE_SELECTED_FALSE 0
#define NODE_SELECTED_TRUE  1

#define annoter_noir 0
#define annoter_blanc 1
struct node
{
    bool exist;
    int idx;
    node_type etat;
    float x; // entre 0 et 1
    float y; // entre 0 et 1
    vec* /*int*/ neightbors;

    int annotation; // Cache pour savoir si on est déjà passer sur le noeud 
    int selected_flag;
    int order;
};
struct join
{
    bool _exist;
    int a;
    int b;

    float distance;

    float distance_opti;
    vec* /*int*/ distance_opti_node_a_passer;
};

float graph_join_get_distance_opti(graph* g, int a, int b);
struct graph
{
    int    _nb; // nb nodes et joins
    node*  _nodes;  
    join** _joins;

    float x_min;
    float x_max;
    float x_etendu;

    float y_min;
    float y_max;
    float y_etendu;
    
    rectf draw_dest;
    bool  draw_text_info;

    bool doit_calculer_distance_opti;
};



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

// ne pas free le vec de retour
vec* graph_node_get_neighbors_vec(graph*g , int _joins);
int graph_get_node_neighbors(graph* g, int idx, int neighbors_idx);

bool graph_join_exist(graph*g, int a, int b);
bool graph_node_exist(graph*g, int idx);

void graph_add_join(graph*g , int a, int b);

float graph_node_x(graph * g , int idx);
float graph_node_y(graph * g , int idx);

void graph_set_node_x_y(graph * g , int idx, float x, float y);

int graph_nb_node_exist(graph * g);
int graph_nb_join_exist(graph * g);

void graph_node_annoter(graph * g, int idx, int val);
void graph_nodes_toute_annoter(graph * g, int val);

bool graph_node_en_blanc(graph* g, int idx);
bool graph_node_en_noir (graph* g, int idx);

void graph_set_order_label(graph* g, vec* path);

void graph_printf(graph* g);

graph* graph_complet(int nb_noeud);

graph* graph_gen_nul_equi(int nb_node, rectf area_contained);
void graph_link_arbre_couvrant(graph* g);
void graph_link_fill_joins(graph* g, float proba);

float path_calculate_length(graph* g, vec* path);
void graph_calculer_distance_opti(graph* g);
vec* graph_recuit_simule(graph* g, float motivation, float(*t_update)(float), float t_start);

graph* graph_generate(int nb_node, rectf area_contained, float proba);

float t_ud_geometric(float t);


#endif