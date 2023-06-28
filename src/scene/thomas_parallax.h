#ifndef THOMAS_PARALLAX_H
#define THOMAS_PARALLAX_H
#include "base.h"

void scene_thomas_parallax_load  (argument arg);
void scene_thomas_parallax_unload(argument arg);

void scene_thomas_parallax_update(argument arg);
void scene_thomas_parallax_draw  (argument arg);

bool scene_thomas_parallax_event (argument arg);
void scene_thomas_parallax_printf(argument arg);

#endif