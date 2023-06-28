#ifndef SCENE_TITRE_H
#define SCENE_TITRE_H
#include "base.h"

void scene_titre_load(context* c, scene* sce);
void scene_titre_unload(context* c, scene* sce);

void scene_titre_update(context* c, scene* sce);
void scene_titre_draw(context* c, scene* sce);

void scene_titre_printf(context* c, scene* sce);

#endif