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

   j->distance_opti = -1;
   j->distance_opti_node_a_passer = vec_empty(int);
}

void node_free(node* n)
{
    vec_free_lazy(n->neightbors);
}

void join_free(join* n)
{
    vec_free_lazy(n->distance_opti_node_a_passer);
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
   g->draw_text_info = true;
   return g;
}

// utilisé pour le cache (doit_calculer_distance_opti)
void graph_was_edited(graph* g)
{
    g->doit_calculer_distance_opti = true;
}

float graph_join_get_distance_opti(graph* g, int a, int b)
{
    if(g->doit_calculer_distance_opti)
    {
        g->doit_calculer_distance_opti = false;
        graph_calculer_distance_opti(g);
    }
    return graph_get_join(g, a, b)->distance_opti;
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
    graph_set_node_x_y(g, i, x, y);
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

void graph_nodes_toute_annoter(graph * g, int val)
{
    repeat(i, graph_get_nb_node(g))
    {
        graph_get_node(g, i)->annotation = val;
    }
}

void graph_node_annoter(graph * g, int idx, int val)
{
    graph_get_node(g, idx)->annotation = val;
}

bool graph_node_en_noir(graph* g, int idx)
{
    return graph_get_node(g, idx)->annotation == annoter_noir;
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

    graph_node_annoter(g, idx, annoter_noir);
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
    graph_nodes_toute_annoter(g, annoter_blanc);

    repeat(i, graph_get_nb_node(g))
    {
        graph_printf_node(g, i);
    }
}

void recalculer_etendu(graph * g)
{
    g->x_etendu = 0;
    g->y_etendu = 0;
    if(graph_get_nb_node(g) == 0) return;

    g->x_min = graph_node_x(g,0);
    g->x_max = graph_node_x(g,0);
    g->y_min = graph_node_y(g,0);
    g->y_max = graph_node_y(g,0);

    repeat(i, graph_get_nb_node(g))
    {
        g->x_min = minif(graph_node_x(g,i), g->x_min);
        g->y_min = minif(graph_node_y(g,i), g->y_min);
        g->x_max = maxif(graph_node_x(g,i), g->x_max);
        g->y_max = maxif(graph_node_y(g,i), g->y_max);
    }

    g->x_etendu = g->x_max - g->x_min;
    g->y_etendu = g->y_max - g->y_min;
}

void graph_set_node_x_y(graph * g , int a, float x, float y)
{
    graph_check_index(g, a);
    graph_get_node(g, a)->x = x;
    graph_get_node(g, a)->y = y;
    recalculer_etendu(g);
    graph_was_edited(g);
    repeat(n, graph_node_get_nb_neighbors(g, a))
    {
        int b = graph_get_node_neighbors(g, a, n);
        update_join_length(g, a, b);
    }
}

graph* graph_complet(int nb_node)
{
    graph* g = graph_empty();
    
    repeat(i, nb_node)
    {
        angle a = from_degree(360.0*i/nb_node);
        graph_add_node_x_y(g, cos(a), sin(a));
    }

    repeat(i, nb_node)
    {
        repeat(j, nb_node)
        {
            graph_add_join(g, i, j);
        }
    }
    return g;
}


graph* graph_gen_nul_equi(int nb_node, rectf area_contained)
{
    graph* g = graph_empty();
    int area = nb_node* 9;
    int tableW = sqrt(area * area_contained.w / area_contained.h);
    int tableH = area / tableW;
    //printf("aire voulue : %d, aire réelle : %d, dim : %d x %d", area, w * h, w, h);

    float cellW = area_contained.w / tableW;
    float cellH = area_contained.h / tableH;

    bool** occuped = create_array(bool*, tableH);
    if (!occuped) {SDL_Log("L'allocation de la colonne a échoué\n"); return null;}

    for (int i = 0; i < tableH; i++)
    {
        occuped[i] = (bool*)calloc(sizeof(bool) * tableW);
        if (!occuped[i]) {SDL_Log("L'allocation de la ligne %d a échoué\n", i); return null;}
    }

    bool crise_du_logement = false;
    while (nb_node > 0 && !crise_du_logement)
    {
        int i, j;
        int it = 0;
        do
        {
            i = rand()%(tableH); j = rand()%(tableW);
            it++;
        } while (occuped[i][j] && it <= area);

        if (it > area) {crise_du_logement = true; SDL_Log("Crise du logement\n");}

        int x = j * cellW + rand()%(int)cellW;
        int y = i * cellH + rand()%(int)cellH;
        graph_add_node_x_y(g, x, y); 
        nb_node--;

        for (int k = -1; k < 2; k++)
        {
            for (int l = -1; l < 2; l++)
            {
                if (!(i+k<0 || i+k >= tableH || j+l < 0 || j+l >= tableW))
                    occuped[i+k][j+l] = true;
            }
        }
    }
    
    for (int i = 0; i < tableH; i++)
    {
        free(occuped[i]);
    }
    free(occuped);
    SDL_Log("Graph nul généré\n");
    
    return g;
}





void graph_link_arbre_couvrant(graph* g)
{
    node* root  = graph_get_node(g, 0);
    root->etat = node_depart;

    int nb_unlk_node = graph_get_nb_node(g) -1;
    int nb_used_node = 1;


    vec* used_nodes = vec_empty(node*);//Nodes déjà liées
    vec* unlk_nodes = vec_empty(node*);//Nodes pas encore liées (unlk -> unlinked)

    vec_add(used_nodes, node*, root);

    for (int i = 1; i < nb_unlk_node+1; i++)
    {
        vec_add(unlk_nodes, node*, graph_get_node(g, i));
    }

    while (nb_unlk_node)
    {
        int unlk_id = rand()%nb_unlk_node;//index dans le vecteur
        int used_id = rand()%nb_used_node;

        node* picked_unlk_node = vec_get(unlk_nodes, node*, unlk_id);
        //node* picked_used_node = vec_get(used_nodes, node*, used_id);
        
        SDL_Log("node liées : %d et %d\n", unlk_id, used_id);
        graph_add_join(g, picked_unlk_node->idx, used_id);
        vec_remove_at(unlk_nodes, unlk_id);
        vec_add(used_nodes, node*, picked_unlk_node);

        nb_unlk_node --;
        nb_used_node ++;
    }
    vec_free_lazy(unlk_nodes);
    vec_free_lazy(used_nodes);
    SDL_Log("Arbre couvrant généré\n");

}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 

void graph_link_fill_joins(graph* g, float proba)
{   
    if (proba > 1) {proba = 1;}
    if (proba > 0.001)
    {
        int p = proba * 1000;
        int nb_node = graph_get_nb_node(g);
        for (int i = 0; i < nb_node; i++)
        {
            for (int j = 0; j < nb_node; j++)
            {
                if (rand()%1000 <= p)
                    graph_add_join(g, i, j);
            }
        }
    }
}

typedef struct
{
    int node_idx;
    float total_length;
    vec* /* int */ chemin;
} reach_info;

reach_info create_reach_info(int node_idx, float total_length, vec* /* int */ chemin)
{
    reach_info r;
    r.node_idx = node_idx;
    r.total_length = total_length;
    r.chemin = chemin;
    return r;
} 

void join_set_distance_opti_parcours(join* j, float distance, vec* /* int */ chemin)
{
    j->distance_opti = distance;
    vec_free_lazy(j->distance_opti_node_a_passer);
    j->distance_opti_node_a_passer = vec_clone(chemin);
}

void graph_calculer_distance_noeud(graph* g, int source)
{   
    #if 0
    graph_check_index(g, source);
    graph_nodes_toute_annoter(g, annoter_blanc);
    graph_node_annoter(g, source, annoter_noir);

    vec* prev = vec_empty(reach_info);
    vec* chemin_source_vers_source = vec_empty(int);
    vec_push(chemin_source_vers_source, int, source);
    vec_push(prev, reach_info, create_reach_info(source, 0, chemin_source_vers_source));

    forever
    {
        float d_min = 10E10;

        int a_prev_idx = -1;
        int best_a = -1;
        int best_b = -1;

        for(int i = 0; i< prev->length; i++)
        {
            reach_info* info = &vec_get(prev, reach_info, i);
            float longueur_depuis_a = info->total_length;
            int a = info->node_idx;

            int a_nb_neighbors = graph_node_get_nb_neighbors(g, a);
            debug;

            for(int k = 0; k < a_nb_neighbors; k++)
            {   
                int b = graph_get_node_neighbors(g, a, k);
                debug;
                if(graph_node_en_noir(g, b)) { continue; } // déjà parcouru
                debug;
                
                join* j = graph_get_join(g, a, b);
                if(!j->exist) { continue; } // le join existe pas
                debug;

                float longueur_pour_aller_sur_b = longueur_depuis_a + j->distance; 
                if(longueur_pour_aller_sur_b < d_min)
                {
                    d_min = longueur_pour_aller_sur_b;
                    a_prev_idx = i;
                    best_a = a;
                    best_b = b;
                }
            }   
        }

        debug;

        if(best_a == -1)
        {
            goto end;
        }

        // on traite le join entre a et b
        printf("a = %i, b = %i\n", best_a, best_b);
        graph_get_join(g, best_a, best_b)->distance_opti = d_min;
        debug;

        vec* /* int */ chemin_vers_best_b = vec_clone(vec_get(prev, reach_info, a_prev_idx).chemin);
        debug;

        vec_push(chemin_vers_best_b, int, best_b);
        debug;

        join_set_distance_opti_parcours(graph_get_join(g, best_a, best_b), d_min, chemin_vers_best_b);
        debug;

        vec_push(prev, reach_info, create_reach_info(best_b, d_min, chemin_vers_best_b));

        graph_node_annoter(g, best_b, annoter_noir);
        debug;

    }

    end:
    debug;

    /*
    while(prev->length > 0)
    {
        debug;
        vec* v = vec_pop(prev, reach_info).chemin;
        debug;
        vec_free_lazy(v);
        debug;
    }*/

    debug;

    
    vec_free_lazy(prev);
    vec_free_lazy(chemin_source_vers_source);
    #endif
}

void graph_calculer_distance_opti(graph* g)
{
    repeat(i, graph_get_nb_node(g))
    {
        repeat(j, graph_get_nb_node(g))
        {
            if(i != j)
            {
                graph_get_join(g, i, j)->distance_opti = 10E10;
                vec_clear(graph_get_join(g, i, j)->distance_opti_node_a_passer);
            }
        }
    }

    repeat(i, graph_get_nb_node(g))
    {
        graph_calculer_distance_noeud(g, i);
    }
}

float path_calculate_length(graph* g, vec* path)
{
    if (path->sizeof_value != sizeof(int)) {SDL_Log("Le chemin passé n'est pas un vecteur de int !!\n"); return -1;}
    int elt_count = path->length;
    if (elt_count <= 1) {return 0;}

    float length = 0;
    for (int i = 0; i < elt_count; i++)
    {
        length += graph_get_join(g, vec_get(path, int, i),
                                    vec_get(path, int, i+1))->distance_opti;
    }
    return length;
}

graph* graph_generate(int nb_node, rectf area_contained, float proba)
{
    graph* newG = graph_gen_nul_equi(nb_node, area_contained);
    graph_link_arbre_couvrant(newG);
    graph_link_fill_joins(newG, proba);
    return newG;
}

vec* graph_recuit_simule(graph* g, float motivation, float(*t_update)(float), float t_start)
{
    int nb_node = graph_get_nb_node(g);
    float t = t_start;

    vec* curr_path = vec_empty(int);
    vec* perm_path;

    vec_add(curr_path, int, node_depart);
    for (int i = 1; i < nb_node; i++)
    {
        vec_add(curr_path, int, node_depart);
    }
    vec_add(curr_path, int, node_depart);
    //curr_path est de la forme [0 1 2 3 4 ... N-1 N 0]

    int nb_no_progress_iter = 0;
    int min_iter = nb_node * motivation;
    while (nb_no_progress_iter < min_iter)
    {    
        perm_path = vec_clone(curr_path);

        int a, b;
        do
        {   a = rand()%(nb_node-1);
            b = rand()%(nb_node-1);
        } while (a == b);

        int tmp = vec_get(perm_path, int, a);
        vec_set(perm_path, int, a, vec_get(perm_path, int, b));
        vec_set(perm_path, int, b, tmp); 

        float curr_length = path_calculate_length(g, curr_path);
        float perm_length = path_calculate_length(g, perm_path);
        float delta = curr_length - perm_length;

        bool swap = false;
        if (delta > 0) {swap = true;}
        else
        {
            float p = expf(-(delta)/t);

            if ( rand()%1000 < (int)(p*1000)) {swap = true;}
            else { nb_no_progress_iter ++;}
        }
        if (swap)
        {
            vec_copy(perm_path, curr_path, 0, perm_path->length, 0);
            nb_no_progress_iter = 0;
        }
        t = t_update(t);
    }
}