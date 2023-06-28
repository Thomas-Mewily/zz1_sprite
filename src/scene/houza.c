#include "base.h"

#define obtenir_state state* s = (state*)(sce->state);

typedef struct 
{
   texture* steve;
   sprite_sheet*ss;
} state;

void scene_houza_load(context* c, scene* sce)
{
    /*
    sce->state = (void*)create(state);

    obtenir_state;
    
    sce->info.background_color = rgb(0,0,255);

    s->steve = texture_create(c, "asset/Steve.png");
    s->ss = sprite_sheet_create(c,)
    */

    
}


void scene_houza_unload(context* c, scene* sce)
{
    obtenir_state;

    texture_free(s->steve);
    free(s);
}

void scene_houza_update(context* c, scene* sce)
{
    obtenir_state;

    if(c->kb_state[SDL_SCANCODE_N])
    {
        scene_set(c,thomas_parallax);
    }
} 

void scene_houza_draw(context* c, scene* sce)
{
    obtenir_state;

    texture* t =  s->steve;
    float scale = 0.5;
    float coef= 0.5;
    sce->info.time;
    //pen_texture_at(c,t,texture_rect(t),c->window_width/2-texture_width(t)/2*scale,c->window_height/2, scale, scale);
    pen_texture_at_center(c,t,texture_rect(t),c->window_width/2,c->window_height/2, scale, scale, coef, coef);
   
    
    pen_color(c, rgb(0,255,255));
    rect  re = rectangle(0,0,0,0);
    rectf rf = rectanglef(0,0,50,50);
    rectf rf2 = rectanglef(c->window_width/2,0,100,100);
    pen_rect(c,rf);
    
    



    //pen_rect(c,)
}

void scene_houza_printf(context* c, scene* sce)
{
    obtenir_state;
    printf("Parallax de houza\n");
}

#undef obtenir_state