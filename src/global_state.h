#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H
#include "base.h"

#define JEU_JOUEUR_QUI_JOUE
#define JEU_FOURMIS_QUI_JOUENT

typedef int jeu_state;
struct the_global_state
{
    // graph du jeu
    graph* g;
    texture* gobelin_texture;

    sprite_sheet* diamant;
    anim* diamant_anim;

    float longueur_rs;

    trajet* path_rs;

    traveler* goblin_traveler;
};


void global_state_load(context* c);
void global_state_unload(context* c);

void global_state_update(context* c);
bool global_state_event(context* c, event* ev);

void global_state_draw(context* c);
void global_state_printf(context* c);

void global_state_new_get_graph(context* c);
#endif