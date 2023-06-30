#include "base.h"

typedef struct 
{
    vec* /*traveler*/ visuel;
    int nb_wave;
    float best_time;
} state;


float simulate_one_stupid_ant(argument arg, graph* g, float testo_to_add, bool add_visual)
{
    obtenir_state;

    // p : puissance pour cette fourmi. p tends vers beaucoup = + court (gloton), t tends vers 0 -> aleatoire
    float p = rand()%RAND_MAX/(float)RAND_MAX * 4.0f;

    vec* node_to_visit = vec_empty(int);
    repeat(i, graph_get_nb_node(g)-1)
    {
        vec_push(node_to_visit, int, i+1);
    }
    vec_printf_int(node_to_visit);

    vec* probas = vec_empty(float);

    trajet* t = trajet_empty();
    trajet_add_node(t, 0);

    graph_nodes_toute_annoter(g, annoter_blanc);
    graph_node_annoter(g, 0, annoter_noir);

    int a = 0;
    float distance = 0;

    while(node_to_visit->length != 0)
    {
        vec_clear(probas);
        float probas_sum = 0;

        repeat(i, node_to_visit->length)
        {
            int b = vec_get(node_to_visit, int, i);
            join* j = graph_get_join(g, a, b);

            //float proba = pow(1.0f/ graph_join_get_distance_opti(g,a,b), p) *j->old_testosterone;
            float proba = (pow(1.0f/ graph_join_get_distance_opti(g,a,b), p) *j->old_testosterone+0.01);
            vec_add(probas, float, proba)
            probas_sum += proba;
        }

        if(probas->length == 0){ add_visual = false; goto end;}

        float choix = (rand() / ((float)RAND_MAX)) * probas_sum;
        int i = 0;
        float proba_cumule = 0;
        do
        {
            proba_cumule += vec_get(probas, float, i);
            i++;
        }while(i < probas->length && proba_cumule < choix);
        i--;

        int n = vec_get(node_to_visit, int, i);
        vec_remove_at(node_to_visit, i);
        trajet_add_node(t, n);
        distance += graph_join_get_distance_opti(g,a,n);
        a = n;
    }
    distance += graph_join_get_distance_opti(g,a,0);

    trajet_add_node(t, 0);

    repeat(i, trajet_length(t)-1)
    {
        a = trajet_get(t, i);
        int b = trajet_get(t, i+1);
        join* j = graph_get_join(g, a, b);
        j->testosterone += testo_to_add; // / graph_join_get_distance_opti(g, a, b);
    }

    end:
    if(add_visual)
    {
        traveler* tr = traveler_create(g, g->rectangle_length*0.5*(1+0.25f*(rand()%1000/1000.0f)));
        vec_push(s->visuel, traveler*, tr);
        tr->node_action = TRAVELER_NODE_ACTION_NOTHINGS;
        traveler_add_travel(tr, t, true);
        traveler_travel_node(tr, 0, true);
        tr->color = hsv(s->nb_wave*43, 1, 1);

        tr->reach_end_action = TRAVELER_END_STOP;
    }
    vec_free_lazy(t);
    vec_free_lazy(probas);
    vec_free_lazy(node_to_visit);
    return distance;
}

void simulate_ants(argument arg, int nb_gen, int nb_ant, bool add_visual)
{
    obtenir_state;
    graph* g = gs->g;
    
    repeat(_, nb_gen)
    {
        if(add_visual)
        {
            s->nb_wave++;
        }else
        {
            repeat(i, graph_get_nb_node(g))
            {
                repeat(j, i)
                {
                    graph_get_join(g, i, j)->old_testosterone = (graph_get_join(g, i, j)->testosterone-0.9f)*0.995+0.9f;
                    graph_get_join(g, i, j)->testosterone = graph_get_join(g, i, j)->old_testosterone;
                }
            }
        }

        repeat(i, nb_ant)
        {
            s->best_time = minif(s->best_time, simulate_one_stupid_ant(arg, g, add_visual ? 0 : (10.0/nb_ant), add_visual));
        }
    }
}

void scene_fourmi_load(argument arg)
{
    obtenir_state;
    s->nb_wave = 0;
    s->best_time = INFINITY;
    s->visuel = vec_empty(traveler*);
}

void scene_fourmi_unload(argument arg)
{
    obtenir_state;
    repeat(i, s->visuel->length)
    {
        traveler* t = vec_get(s->visuel, traveler*, i);
        traveler_free(t);
    }
    vec_free_lazy(vec_empty(traveler*));
}

void scene_fourmi_update(argument arg)
{
    obtenir_state;

    if(c->nb_update % 60 == 0)
    {
        simulate_ants(arg, 1, 100, true);
    }
    if(c->nb_update % (graph_get_nb_node(gs->g)) == 0)
    {
        simulate_ants(arg, 1, 500, false);
    }

    for(int i = s->visuel->length-1; i >= 0; i--)
    {
        traveler* t = vec_get(s->visuel, traveler*, i);
        if(t->state == TRAVELER_STATE_WAIT)
        {
            traveler_free(t);
            vec_remove_at(s->visuel, i);
            continue;
        }
        traveler_update(c, t);
    }
} 

void scene_fourmi_draw(argument arg)
{
    obtenir_state;

    pen_color(c, color_red);
    graph* g = gs->g;

    repeat(i, s->visuel->length)
    {
        traveler* t = vec_get(s->visuel, traveler*, i);
        float size = 16;
        
        float sizeX = size;
        float sizeY = size;
        pen_color(c, t->color);

        float x = camera_graph2cam_x(c,g,t->x);
        float y = camera_graph2cam_y(c,g,t->y);

        rectf dest = rectanglef(x-sizeX/2, y-sizeY/2, sizeX,sizeY);
        pen_rect(c, dest);
    }

    // Cancel camera zoom
    camera_state cs = camera_get_state(c);
    camera_set_state(c, camera_state_default());
    // Not affected by scrolling or scalling
    pen_formatted_text_at_center(c, 0, 0, FONT_SIZE_NORMAL, 0, 0, "Temps Fourmi : %.1f", s->best_time);
    camera_set_state(c, cs);

    pen_graph(c, gs->g);
}

bool scene_fourmi_event (argument arg) { obtenir_state; return false; }
void scene_fourmi_printf(argument arg) 
{ 
    obtenir_state;
    printf("Fourmis\n");
    repeat(i, s->visuel->length)
    {
        traveler* t = vec_get(s->visuel, traveler*, i);
        traveler_free(t);
    }
    s->best_time = INFINITY;
    vec_clear(s->visuel);
}