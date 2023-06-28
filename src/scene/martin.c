#include "base.h"

typedef struct 
{
   float hue;
   float color_change_speed;
   texture* steve;
   sprite_sheet* froggyS;
   anim* froggyAnim;
} state;

void set_bg_color(argument arg)
{
    obtenir_state;
    sce->info.background_color = hsv(s->hue, 0.4, 0.95);
}

void scene_martin_load(argument arg)
{   
    obtenir_state;

    s->hue = 0;
    s->color_change_speed = 0.7;
    set_bg_color(arg);
    s->steve = texture_create(c, "asset/steve.png");
    s->froggyS = sprite_sheet_create(c, "asset/froggyChair.png", 54, 54);
    s->froggyAnim = animation_create(s->froggyS, frequence_s(20));
}

void scene_martin_unload(argument arg)
{
    obtenir_state;
    texture_free(s->steve);
}

void scene_martin_update(argument arg)
{
    obtenir_state;
    set_bg_color(arg);
    s->hue += s->color_change_speed;
    if (s->hue >= 360) {s->hue = 0;}

    c->pen_x = (c->window_width/2) -  c->mouse_x;
    c->pen_y = (c->window_height/2) -  c->mouse_y;

}
void scene_martin_draw(argument arg)
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

void scene_martin_event (argument arg) { obtenir_state; }
void scene_martin_printf(argument arg) { obtenir_state; }