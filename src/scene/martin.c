#include "base.h"

#define obtenir_state scene_martin_state* s = (scene_martin_state*)(sce->state);

typedef struct 
{
   float hue;
   float color_change_speed;
} scene_martin_state;

void set_bg_color(scene* sce)
{
    obtenir_state;
    sce->info.background_color = hsv(s->hue, 0.4, 0.95);
}

void scene_martin_load(context* c, scene* sce)
{
    sce->state = (void*)create(scene_martin_state);
    obtenir_state;

    s->hue = 0;
    s->color_change_speed = 1.3;
    set_bg_color(sce);


}
void scene_martin_unload(context* c, scene* sce)
{
    free(sce->state);
}

void scene_martin_update(context* c, scene* sce)
{
    obtenir_state;
    set_bg_color(sce);
    s->hue += s->color_change_speed;
    if (s->hue >= 360) {s->hue = 0;}

}
void scene_martin_draw(context* c, scene* sce)
{
    return;
}

void scene_martin_printf(context* c, scene* sce)
{
    return;
}