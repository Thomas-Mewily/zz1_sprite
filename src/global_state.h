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
    sprite_sheet* goblinS;

    anim* goblin_anim_down_walk;
    anim* goblin_anim_right_walk;
    anim* goblin_anim_up_walk;
    anim* goblin_anim_left_walk;

    anim* goblin_anim_down_idle;
    anim* goblin_anim_right_idle;
    anim* goblin_anim_up_idle;
    anim* goblin_anim_left_idle;
};

void global_state_load(context* c);
void global_state_unload(context* c);

void global_state_update(context* c);
bool global_state_event(context* c, event* ev);
void global_state_draw(context* c);
#endif