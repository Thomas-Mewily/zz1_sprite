#ifndef GRAPH_H
#define GRAPH_H
#include "base.h"

#if 0
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
} node;

void node_init(graph* g, int16 idx)
{
   node* n = graph_get_node(g, idx);
   n->idx = idx;
   n->exist = false;
   n->x = 0;
   n->y = 0;
   n->neightbors = vec_empty(int);
}

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

#define graph_for_loop_in_neighbors_idx(graph, idx, neigbors_var_name)\
for(int neigbors_var_name = 0;i<graph_node_get_nb_neighbors(g,idx);neigbors_var_name++)

void graph_check_index(graph* g, int idx)
{
   check(idx >= 0 && idx < g->nb);
}

int graph_node_get_nb_neighbors(graph* g, int idx)
{
   return graph_get_node(g, idx)->neightbors->length;
}

int graph_get_nb_node(graph* g){
   int nb = g->_nb;
   return nb;
}


node* graph_get_node(graph* g , int idx)
{
   graph_check_index(idx);
   return g->_nodes[idx];
}

join* graph_get_join(graph*g, int a, int b)
{
   if(a == b) { return null; }
   if(a  < b) { return graph_get_join(g, b, a); }

   // a > b
   graph_check_index(a);
   graph_check_index(b);
   return g->_joins[a][b];
}

graph* graph_create(){
   graph* g = create(graph);
   int nb_noeud = 0;
   g->_nodes = null; //create_array(node,  nb_noeud);
   g->_joins = null; //create_array(join*, nb_noeud);
}

void * graph_free(graph*g){
   repeat(x, graph_get_nb_node(g))
   {
      free(g->_joins[x]);
   }
   free(g->_nodes);
   free(g);
   g->_nb = 0;
   g->_joins = null;
   g->_nodes = null;
}

vec* graph_node_get_neighbors(graph*g , int indice){
   return g->_nodes->neightbors;
}

bool graph_node_exist(a, b)
{

}

void graph_add_join(graph*g , int a , int b){

   if()
   join* j =graph_get_join(g ,a ,b);
   j->exist=true;
   j->distance=length(graph_node_x(g,a),graph_node_y(g,a),graph_node_x(g,b),graph_node_y(g,b));
   
}

float graph_node_x(graph * g , int a) { return g->_nodes[a].x; }
float graph_node_y(graph * g , int a) { return g->_nodes[a].y; }

float graph_set_node_x_y(graph * g , int idx, float x, float y) 
{ 
   g->_nodes[idx].x = x;
   g->_nodes[idx].y = y;

}
#endif


#endif