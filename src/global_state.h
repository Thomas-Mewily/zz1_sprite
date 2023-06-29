#ifndef GLOBAL_STATE_H
#define GLOBAL_STATE_H
#include "base.h"

struct the_global_state
{
    graph* g;
};

void global_state_load(context* c);
void global_state_unload(context* c);
#endif