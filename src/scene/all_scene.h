#include "../base.h"

#define get_state \
scene* sce = (arg.arg_scene); \
context* c = (arg.arg_context); \
if(sce->state == null) { sce->state = (void*)create(state); }\
state* s   = (state*)(sce->state); \
scene_info* info = &(sce->info); \
event* ev = (arg.arg_event); \
UNUSED(c);   \
UNUSED(sce); \
UNUSED(s);   \
UNUSED(info);\
UNUSED(ev);  \


// recupère : scene* sce, state* s, scene_info* info, event* ev , (+ malloc également automatiquement la structure nommé "state" et l'associe à la scene)
#define obtenir_state get_state

// pour les paramètres de fonction "non utilisé" dans les scenes (load, unload, update...) qui sont référencé par des pointeurs de fonction
//#pragma GCC diagnostic ignored "-Wunused-parameter"

#include "titre.h"
#include "thomas_parallax.h"
#include "houza.h"
#include "martin.h"
#include "graph_joueur.h"
#include "fourmi.h"

//#pragma GCC diagnostic warning "-Wunused-parameter"