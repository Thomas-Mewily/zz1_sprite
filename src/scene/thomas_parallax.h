#ifndef THOMAS_PARALLAX_H
#define THOMAS_PARALLAX_H
#include "base.h"

void scene_thomas_parallax_load(context* c, scene* sce);
void scene_thomas_parallax_unload(context* c, scene* sce);

void scene_thomas_parallax_update(context* c, scene* sce);
void scene_thomas_parallax_draw(context* c, scene* sce);

void scene_thomas_parallax_printf(context* c, scene* sce);

#endif