#ifndef GRAPH_JOUEUR_H
#define GRAPH_JOUEUR_H
#include "base.h"

void scene_graph_joueur_load  (argument arg);
void scene_graph_joueur_unload(argument arg);

void scene_graph_joueur_update(argument arg);
void scene_graph_joueur_draw  (argument arg);

bool scene_graph_joueur_event (argument arg);
void scene_graph_joueur_printf(argument arg);

#endif