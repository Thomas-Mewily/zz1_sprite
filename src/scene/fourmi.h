#ifndef FOURMI_H
#define FOURMI_H
#include "base.h"

void scene_fourmi_load  (argument arg);
void scene_fourmi_unload(argument arg);

void scene_fourmi_update(argument arg);
void scene_fourmi_draw  (argument arg);

bool scene_fourmi_event (argument arg);
void scene_fourmi_printf(argument arg);

#endif