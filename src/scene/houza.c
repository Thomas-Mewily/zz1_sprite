#include "base.h"
#include <stdlib.h>

#define obtenir_state state* s = (state*)(sce->state);

typedef struct 
{
   //texture* steve;
   
} state;

void scene_houza_load(context* c, scene* sce)
{
    
    sce->state = (void*)create(state);

    obtenir_state;
    
    sce->info.background_color = rgb(200,0,0);

    //s->steve = texture_create(c, "asset/Steve.png");
}


void scene_houza_unload(context* c, scene* sce)
{
    obtenir_state;

   // texture_free(s->steve);
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

   #if 0
    //texture* t =  s->steve;
    float scale = 0.5;
    float coef= 0.5;
    sce->info.time;
    //pen_texture_at(c,t,texture_rect(t),c->window_width/2-texture_width(t)/2*scale,c->window_height/2, scale, scale);
   // pen_texture_at_center(c,t,texture_rect(t),c->window_width/2,c->window_height/2, scale, scale, coef, coef);
   

    int nb_cercle = 5;
    int i =0;
    int j=0;
    int poX[nb_cercle];
    for(i=0;i<nb_cercle;i++){
        poX[i]=rand()%c->window_width;
        printf("%d ",poX[i]);

    }
    int posX1 = rand()%c->window_width;
    int posX2 = rand()%c->window_width;
    int posY1 = rand()%c->window_height;
    int posY2 = rand()%c->window_height;
    int posX3 = rand()%c->window_width;
    int posY3 = rand()%c->window_height;
    int posX4 = rand()%c->window_width;
    int posY4 = rand()%c->window_height;
    int posX5 = rand()%c->window_width;
    int posY5 = rand()%c->window_height;
    int radius = 20;

    pen_color(c, rgb(255,255,255));
    for(j=0;j<nb_cercle;j++){

    pen_circle(c,poX[j],posY1,radius);
   /* pen_circle(c,posX2,posY2,radius);
    pen_circle(c,posX3,posY3,radius);
    pen_circle(c,posX4,posY4,radius);
    pen_circle(c,posX5,posY5,radius);
    pen_line(c,poX[i],posY1,posX2,posY2);*/
  /*  pen_line(c,posX2,posY2,posX3,posY3);
    pen_line(c,posX3,posY3,posX4,posY4);
    pen_line(c,posX4,posY4,posX5,posY5);
    pen_line(c,posX5,posY5,posX1,posY1);*/
    SDL_Delay(1000);}   
    
   
    
   // rectf rf = rectanglef(0,0,50,50);
  
   // pen_rect(c,rf);
   #endif
}


void scene_houza_printf(context* c, scene* sce)
{
    obtenir_state;
    printf("Parallax de houza\n");
}

#undef obtenir_state