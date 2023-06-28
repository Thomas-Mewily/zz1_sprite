#include "base.h"

void node_init(graph* g, int idx)
{
   node* n = graph_get_node(g, idx);
   n->idx = idx;
   n->exist = false;
   n->x = 0;
   n->y = 0;
   n->neightbors = vec_empty(int);
}

void join_init(join* j, int a, int b)
{
   j->a = a;
   j->b = b;
   j->exist = false;
}

void node_free(node* n)
{
    vec_free_lazy(n->neightbors);
}

void join_free(join* n)
{
    (void)n;
    // rien à faire
}


void graph_check_index(graph* g, int idx)
{
   check(idx >= 0 && idx < graph_get_nb_node(g));
}

int graph_node_get_nb_neighbors(graph* g, int idx)
{
   return graph_node_get_neighbors_vec(g, idx)->length;
}

int graph_get_nb_node(graph* g){
   int nb = g->_nb;
   return nb;
}


node* graph_get_node(graph* g , int idx)
{
   graph_check_index(g, idx);
   return &(g->_nodes[idx]);
}

join* graph_get_join(graph*g, int a, int b)
{
   if(a == b) { return null; }
   if(a  < b) { return graph_get_join(g, b, a); }

   // a > b
   graph_check_index(g, a);
   graph_check_index(g, b);
   return &(g->_joins[a][b]);
}

graph* graph_empty()
{
   graph* g = create(graph);
   g->_nodes = null;
   g->_joins = null;
   g->_nb = 0;
   return g;
}

void graph_free(graph* g)
{
   repeat(i, graph_get_nb_node(g))
   {
        repeat(j, i)
        {
            if(graph_join_exist(g, i, j))
            {
                join_free(graph_get_join(g, i, j));
            }
        }
        node_free(&(g->_nodes[i]));
        free(g->_joins[i]);
   }
   free(g->_joins);
   free(g->_nodes);
   g->_nb = 0;
   g->_joins = null;
   g->_nodes = null;
   free(g);
}

vec* graph_node_get_neighbors_vec(graph*g , int idx){
   return g->_nodes[idx].neightbors;
}

bool graph_join_exist(graph*g, int a, int b) 
{ 
    if(a == b) { return false; }
    return graph_get_join(g, a, b)->exist;
}
bool graph_node_exist(graph*g, int idx)      { return graph_get_node(g, idx)->exist;  }

void update_join_length(graph*g , int a , int b)
{
    join* j = graph_get_join(g ,a ,b);
    j->distance = length(graph_node_x(g,a),graph_node_y(g,a),graph_node_x(g,b),graph_node_y(g,b));
}

void graph_add_join(graph*g , int a , int b)
{
    bool a_exist = graph_node_exist(g, a);
    bool b_exist = graph_node_exist(g, b);
    bool j_exist = graph_join_exist(g, a, b);
    if(a_exist && b_exist && (j_exist == false) && a != b)
    {
        graph_get_join(g ,a ,b)->exist = true;
        update_join_length(g, a, b);
        vec_add(graph_get_node(g, a)->neightbors, int, b);
        vec_add(graph_get_node(g, b)->neightbors, int, a);
    }
}

float graph_node_x(graph * g , int idx) { return g->_nodes[idx].x; }
float graph_node_y(graph * g , int idx) { return g->_nodes[idx].y; }

int graph_add_node_x_y(graph* g, float x, float y) 
{ 
    g->_nodes = realloc(g->_nodes, (g->_nb+1)*sizeof(node));
    g->_joins = realloc(g->_joins, (g->_nb+1)*sizeof(join*));
    g->_joins[g->_nb] = create_array(join, g->_nb);
    int i = g->_nb;
    repeat(j, g->_nb)
    {
        join_init(&(g->_joins[g->_nb][j]), i, j);
    }
    g->_nb++;

    node_init(g, i);
    g->_nodes[i].x = x;
    g->_nodes[i].y = y;
    g->_nodes[i].exist = true;
    return g->_nb-1;
}

int graph_nb_node_exist(graph * g)
{
    int nb_node = 0;
    repeat(i, graph_get_nb_node(g))
    {
        if(graph_node_exist(g, i))
        {
            nb_node++;
        }
    }
    return nb_node;
}
int graph_nb_join_exist(graph * g)
{
    int nb_join = 0;
    repeat(i, graph_get_nb_node(g))
    {
        repeat(j, i)
        {
            if(graph_join_exist(g, i, j))
            {
                nb_join++;
            }
        }
    }
    return nb_join;
}

void graph_colorier_nodes_blanc(graph * g)
{
    repeat(i, graph_get_nb_node(g))
    {
        graph_get_node(g, i)->colorer_en_noir = false;
    }
}

void graph_node_colorier_blanc(graph * g, int idx)
{
    graph_get_node(g, idx)->colorer_en_noir = false;
}
void graph_node_colorier_noir(graph * g, int idx)
{
    graph_get_node(g, idx)->colorer_en_noir = true;
}

bool graph_node_en_noir(graph* g, int idx)
{
    return graph_get_node(g, idx)->colorer_en_noir;
}

bool graph_node_en_blanc(graph* g, int idx)
{
    return !graph_node_en_noir(g, idx);
}

int graph_get_node_neighbors(graph* g, int idx, int neighbors_idx)
{
    return vec_get(graph_get_node(g, idx)->neightbors, int, neighbors_idx);
}

void graph_printf_node(graph* g, int idx)
{
    // déjà traité
    if(graph_node_en_noir(g, idx)) { return; }

    graph_node_colorier_noir(g, idx);
    printf("node %i {%.2f, %.2f}. neighbors : [", idx, graph_node_x(g, idx), graph_node_y(g, idx));

    repeat(n, graph_node_get_nb_neighbors(g, idx))
    {
        int n_idx = graph_get_node_neighbors(g, idx, n);
        printf("(%i : %f), ", n_idx, graph_get_join(g, idx, n_idx)->distance);
    }
    //vec_printf_int(graph_get_node(g, idx)->neightbors);
    printf("]\n");


}

void graph_printf(graph* g)
{
    printf("graph de %i node and %i joins : [(idx, length)]\n", graph_nb_node_exist(g), graph_nb_join_exist(g));
    graph_colorier_nodes_blanc(g);

    repeat(i, graph_get_nb_node(g))
    {
        graph_printf_node(g, i);
    }
}

graph* graph_complet(int nb_node, float radius)
{
    graph* g = graph_empty();
    
    repeat(i, nb_node)
    {
        angle a = from_degree(360.0*i/nb_node);
        graph_add_node_x_y(g, cos(a)*radius, sin(a)*radius);
    }

    repeat(i, nb_node)
    {
        repeat(j, nb_node)
        {
            graph_add_join(g, i, j );
            
            if( ((5*i+7*j)%100) < 50)
            { // maybe add a join
              // graph_add_join(g, i, j );
            }
        }
    }
    return g;
}

void graph_set_node_x_y(graph * g , int a, float x, float y)
{
    graph_check_index(g, a);
    graph_get_node(g, a)->x = x;
    graph_get_node(g, a)->y = y;
    repeat(n, graph_node_get_nb_neighbors(g, a))
    {
        int b = graph_get_node_neighbors(g, a, n);
        update_join_length(g, a, b);
    }
}