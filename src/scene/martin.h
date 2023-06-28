#ifndef SCENE_MARTIN_H
#define SCENE_MARTIN_H
#include "base.h"

void scene_martin_load(context* c, scene* sce);
void scene_martin_unload(context* c, scene* sce);

void scene_martin_update(context* c, scene* sce);
void scene_martin_draw(context* c, scene* sce);

void scene_martin_printf(context* c, scene* sce);

#endif