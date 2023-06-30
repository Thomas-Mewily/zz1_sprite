#include "base.h"

#define nb_parallax 4
#define load_parallax(idx) texture_create(c, "asset/parallax" #idx ".png")

typedef struct 
{
   texture* parallax[4];
   sprite_sheet* ss;
   anim* knight;
   float time_offset;
} state;

void scene_thomas_parallax_load(argument arg)
{
    obtenir_state;

    sce->info.background_color = rgb(107, 51, 135);

    s->parallax[0] = load_parallax(1);
    s->parallax[1] = load_parallax(2);
    s->parallax[2] = load_parallax(3);
    s->parallax[3] = load_parallax(4);

    s->ss = sprite_sheet_create(c, "asset/knight_ko.png", 24, 32);
    s->knight = animation_create(s->ss, frequence_s(10));
    s->time_offset = 0;
}

void scene_thomas_parallax_unload(argument arg)
{
    obtenir_state;
    
    repeat(i, nb_parallax)
    {
        texture_free(s->parallax[i]);
    }

    sprite_sheet_free(s->ss);
    animation_free(s->knight);
}

void scene_thomas_parallax_update(argument arg)
{
    obtenir_state;

    // todo utiliser & faire les macro inputs : pull 
    if(c->kb_state[SDL_SCANCODE_SPACE])
    {
        s->time_offset = sce->info.time;
    }
    if(c->kb_state[SDL_SCANCODE_N])
    {
        scene_set(c,titre);
    }
} 

void scene_thomas_parallax_draw(argument arg)
{
    obtenir_state;

    float mX = -(c->mouse_x - (float)c->window_width /2)/(c->window_width /2);
    float mY = -(c->mouse_y - (float)c->window_height/2)/(c->window_height/2);

    float hole_x = 0;
    float hole_y = 0;
    for(int i = nb_parallax-1; i >= 0; i--)
    {
        float j = (i-((nb_parallax-1)/2.0))/((nb_parallax-1)/2.0);
        float dest_x = c->window_width /2 + mX*(j)*c->window_height/8;
        float dest_y = c->window_height/2 + mY*(j)*c->window_height/8;
        texture* t = s->parallax[i];
        float scale = (1-j*0.5-length(0,0, mX, mY*c->window_ratio_width_div_height)/16)*(1+abs(j*0.5));
        float scaleX = scale/texture_width(t);
        float scaleY = scale/texture_height(t);
        pen_texture_at_center(c, t, texture_rect(t), dest_x, dest_y, scaleX*c->window_width, scaleY*c->window_height, 0.5, 0.5);
    
        if(i == nb_parallax-1)
        {
            hole_x = dest_x;
            hole_y = dest_y;
        }
    }

    int knight_anim_height = animation_height(s->knight);
    float scaleY = (int)(1.0/knight_anim_height*c->window_height/8);
    float timer = second(sce->info.time)-s->time_offset;
    float fall_scale = scaleY+scaleY*abs(sin(timer*2*pi/4))*8/(timer*timer);
    
    pen_animation_at_center(c, s->knight, hole_x, hole_y, fall_scale, fall_scale, 0.5, 0.5, sce->info.time);
}

bool scene_thomas_parallax_event (argument arg) { obtenir_state; return false; }
void scene_thomas_parallax_printf(argument arg) { obtenir_state; printf("Parallax de Thomas\n"); }

#undef obtenir_state