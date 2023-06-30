#include "base.h"

typedef struct 
{
    jeu_state qui_joue;
    vec* /*of ants */ ants;
} state;

void scene_fourmi_load(argument arg)
{
    obtenir_state;
    /*

    s->ants = vec_empty(ant);
    repeat(i, 50)
    {
        
    }*/
}

void scene_fourmi_unload(argument arg)
{
    obtenir_state;
    
}

void scene_fourmi_update(argument arg)
{
    obtenir_state;
} 

void scene_fourmi_draw(argument arg)
{
    obtenir_state;

}

bool scene_fourmi_event (argument arg) { obtenir_state; return false; }
void scene_fourmi_printf(argument arg) { obtenir_state; printf("Fourmis\n"); }