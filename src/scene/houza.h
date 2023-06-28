#ifndef HOUZA_H
#define HOUZA_H
#include "base.h"

void scene_houza_load(context* c, scene* sce);
void scene_houza_unload(context* c, scene* sce);

void scene_houza_update(context* c, scene* sce);
void scene_houza_draw(context* c, scene* sce);

void scene_houza_printf(context* c, scene* sce);

#endif