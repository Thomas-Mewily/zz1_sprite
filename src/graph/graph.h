#ifndef GRAPH_H
#define GRAPH_H
#include "base.h"

/*
#define node_depart 0
#define node_deja_visiter 1
#define node_a_visiter 2

typedef node_state int;

struct graph;

typedef struct
{
    bool exist;
    int idx;
    node_state etat;
    float x;
    float y;
} node;

typedef struct
{
    bool exist;
    int a;
    int b;
    float distance;

} join;

struct graph {
    int    _nb; // nb nodes et joins
    node*  _nodes;  
    join** _joins;
};
typedef struct graph graph; 

int graph_get_nb_node(graph* g){
   int nb = g->_nb;
   return nb;
}



node* graph_get_node(graph* g , int indice){
   node* node = g->_nodes[indice];

   return node ,;
}

join* graph_get_join(graph*g ,int a , int b ){


}

graph* graph_create(int nb_noeud ){
   graph* g = create(graph);
   g->_nb = nb_noeud;
   g->_nodes = create_array(node,nb_noeud);
   g->_joins = create_array(join*, nb_noeud);
}

void * graph_free(graph*g){
   free(g->_nodes);
   todo join
   free(g);

}

vec* graph_node_get_neighbors(graph*g , int indice){

}

void graph_add_join(graph*g , int a , int b){

   join* j =graph_get_join(g ,a ,b);
   j->exist=true;
   j->distance=length(graph_node_x(g,a),graph_node_y(g,a),graph_node_x(g,b),graph_node_y(g,b));
   
}

float graph_node_x(graph * g , int a){
   return g->_nodes[a].x;
}
float graph_node_y(graph * g , int a){
   return g->_nodes[a].y;
}
*/
#endif