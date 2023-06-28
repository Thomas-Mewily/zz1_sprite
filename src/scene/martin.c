#include "base.h"

#define obtenir_state scene_martin_state* s = (scene_martin_state*)(sce->state);

typedef struct 
{
   float hue;
   float color_change_speed;
   texture* steve;
   sprite_sheet* froggyS;
   anim* froggyAnim;
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
    s->color_change_speed = 0.7;
    set_bg_color(sce);
    s->steve = texture_create(c, "asset/steve.png");
    s->froggyS = sprite_sheet_create(c, "asset/froggyChair.png", 54, 54);
    s->froggyAnim = animation_create(s->froggyS, frequence_s(20));


}
void scene_martin_unload(context* c, scene* sce)
{
    obtenir_state;
    SDL_DestroyTexture(s->steve);
    free(sce->state);
}

void scene_martin_update(context* c, scene* sce)
{
    obtenir_state;
    set_bg_color(sce);
    s->hue += s->color_change_speed;
    if (s->hue >= 360) {s->hue = 0;}

    c->pen_x = (c->window_width/2) -  c->mouse_x;
    c->pen_y = (c->window_height/2) -  c->mouse_y;


}
void scene_martin_draw(context* c, scene* sce)
{
    obtenir_state;
    //pen_circle(c, 100, 100, 50 );
    pen_text_at(c, "QUOI? azertyuiopqsdfgjhklwxcvbnvc", 0, 0, FONT_SIZE_FULLSCREEN);
    pen_text_at(c, "QUOI? azertyuiopqsdfgjhklwxcvbnvc", 0, 50, FONT_SIZE_BIG);
    pen_text_at(c, "QUOI? azertyuiopqsdfgjhklwxcvbnvc", 0, 100, FONT_SIZE_NORMAL);
    pen_text_at(c, "QUOI? azertyuiopqsdfgjhklwxcvbnvc", 0, 200, FONT_SIZE_SMALL);
    pen_rect(c, rectanglef(400, 20, 100,20));
    pen_texture_at(c, s->steve, texture_rect(s->steve), 400, 300, 1, 1);
    pen_animation_at(c, s->froggyAnim, 10, 400, 3, 3, c->timer);
}

void scene_martin_printf(context* c, scene* sce)
{
    return;
}