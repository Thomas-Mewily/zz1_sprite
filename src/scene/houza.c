#include "base.h"
#include <stdlib.h>

typedef struct 
{
   //texture* steve;
   graph* g;
   ant* a;
} state;

void scene_houza_load(argument arg)
{
    obtenir_state;

    s->g = graph_complet(20,1);
    //s->a = ant_create(s->a);

    sce->info.background_color = rgb(200,0,0);
    //graph_printf(s->g);
    //s->steve = texture_create(c, "asset/Steve.png");
}


void scene_houza_unload(argument arg)
{
    obtenir_state;
    graph_free(s->g);

    
   // texture_free(s->steve);
}

void scene_houza_update(argument arg)
{
    obtenir_state;
    ant_update(10,s->a);

    if(c->kb_state[SDL_SCANCODE_N])
    {
        scene_set(c,thomas_parallax);
    }
} 

void scene_houza_draw(argument arg)
{
    obtenir_state;
    

    //pen_graph(c, s->g);

    #if 0
    float radius = c->screen_height/32.0f;

    float scale = c->window_height/2-radius;
    float offset_x = c->window_width/2;
    float offset_y = c->window_height/2;



    pen_color(c,color_white);
    graph* g = s->g;
    ant* a = s->a;

    //graph_get_join(g,0,1).distance
    repeat(i, graph_get_nb_node(g))
    {
        pen_color(c,color_white);

        float x = graph_node_x(g,i);
        float y = graph_node_y(g,i);
        pen_circle(c,scale*x +offset_x,scale*y+offset_y ,radius);
        
        
        for(int k = 0; k < graph_node_get_nb_neighbors(g,i); k++)
        {
            int j = graph_get_node_neighbors(g,i,k);
            float xj = graph_node_x(g,j);
            float yj =graph_node_y(g,j);
            pen_line(c,scale*x +offset_x,scale*y+offset_y,scale*xj +offset_x,scale*yj+offset_y);
        }
    }
    #endif


   rectf fourmis = rectanglef(10,10  ,20,20);
    pen_rect(c,fourmis);
   

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

bool scene_houza_event (argument arg) { obtenir_state; return false; }
void scene_houza_printf(argument arg)
{
    obtenir_state;
    printf("Parallax de houza\n");
}