#ifndef HOUZA_H
#define HOUZA_H
#include "base.h"

void scene_houza_load  (argument arg);
void scene_houza_unload(argument arg);

void scene_houza_update(argument arg);
void scene_houza_draw  (argument arg);

bool scene_houza_event (argument arg);
void scene_houza_printf(argument arg);
#endif