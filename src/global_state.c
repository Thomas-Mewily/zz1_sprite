#include "base.h"
#define FPS_IDLE 500
#define FPS_WALK 200

void get_graph(context* c)
{
    if(gs->g != null)
    {
        graph_free(gs->g);
    }

    //gs->g = graph_generate(100, rectanglef(0, 0, 160, 90), 0.25f);
    gs->g = graph_generate(8, rectanglef(0, 0, 16, 9), 0.25f);
    //gs->g = graph_complet(8);
    graph* g = gs->g;

    repeat(i, graph_get_nb_node(g))
    {
        repeat(j, graph_get_nb_node(g))
        {
            if(i == j) continue;
            
            float futur_distance = graph_get_join(g,i,j)->distance * (rand()%4+1);
            graph_join_set_distance(g, i, j, futur_distance);
        }
    }
}

void global_state_load(context* c)
{
    gs = create(the_global_state);
    gs->g = null;
    get_graph(c);

    

    /*
    gs->g = graph_empty();

    graph* g = gs->g;
    
    int a = graph_add_node_x_y(g, 0,  0);
    int b = graph_add_node_x_y(g, 1,  0);
    int x = graph_add_node_x_y(g, 1, -1);
    int y = graph_add_node_x_y(g, 0.7, -2);
    int z = graph_add_node_x_y(g, 1.5, -1.5);
    graph_add_join(g, a, b);
    graph_add_join(g, b, x);
    graph_add_join(g, x, y);
    graph_add_join(g, y, z);
    graph_add_join(g, z, x);
    */

    gs->goblinS = sprite_sheet_create(c, "asset/goblin.png", 24, 32);

    gs->goblin_anim_down_walk = animation_create(gs->goblinS, FPS_WALK);
    gs->goblin_anim_down_walk->first_frame = 8; 
    gs->goblin_anim_down_walk->last_frame = 11; 
    gs->goblin_anim_right_walk = animation_create(gs->goblinS, FPS_WALK);
    gs->goblin_anim_right_walk->first_frame = 12; 
    gs->goblin_anim_right_walk->last_frame = 15; 
    gs->goblin_anim_up_walk = animation_create(gs->goblinS, FPS_WALK);
    gs->goblin_anim_up_walk->first_frame = 16; 
    gs->goblin_anim_up_walk->last_frame = 19; 
    gs->goblin_anim_left_walk = animation_create(gs->goblinS, FPS_WALK);
    gs->goblin_anim_left_walk->first_frame = 20; 
    gs->goblin_anim_left_walk->last_frame = 23; 

    gs->goblin_anim_down_idle = animation_create(gs->goblinS, FPS_IDLE);
    gs->goblin_anim_down_idle->first_frame = 0; 
    gs->goblin_anim_down_idle->last_frame = 1; 
    gs->goblin_anim_right_idle = animation_create(gs->goblinS, FPS_IDLE);
    gs->goblin_anim_right_idle->first_frame = 2; 
    gs->goblin_anim_right_idle->last_frame = 3; 
    gs->goblin_anim_up_idle = animation_create(gs->goblinS, FPS_IDLE);
    gs->goblin_anim_up_idle->first_frame = 4; 
    gs->goblin_anim_up_idle->last_frame = 5; 
    gs->goblin_anim_left_idle = animation_create(gs->goblinS, FPS_IDLE);
    gs->goblin_anim_left_idle->first_frame = 6; 
    gs->goblin_anim_left_idle->last_frame = 7; 
}

void global_state_unload(context* c)
{
    free_animation(gs->goblin_anim_down_walk);
    free_animation(gs->goblin_anim_right_walk);
    free_animation(gs->goblin_anim_up_walk);
    free_animation(gs->goblin_anim_left_walk);

    free_animation(gs->goblin_anim_down_idle);
    free_animation(gs->goblin_anim_right_idle);
    free_animation(gs->goblin_anim_up_idle);
    free_animation(gs->goblin_anim_left_idle);
    sprite_sheet_free(gs->goblinS);

    graph_free(gs->g);
    free(gs);
}

void global_state_update(context* c)
{
    gs->g->draw_dest = window_rectf(c);

    /*
    if(c->nb_update % 10)
    {
        printf("%.3f, %.3f\n", camera_pixel_pos_2_graph_pos_x(c, gs->g, input_mouse_x(c)),
                                              camera_pixel_pos_2_graph_pos_y(c, gs->g, input_mouse_y(c))
                                              );
    }*/
}

void global_state_draw(context* c)
{
    pen_graph(c, gs->g);
}

void global_state_printf(context* c)
{
    get_graph(c);

}


bool global_state_event(context* c, event* ev)
{
    switch (ev->type)
    {
        case SDL_KEYDOWN:
        {
            switch (ev->key.keysym.sym)
            {
                case SDLK_g: gs->g->draw_text_info = (gs->g->draw_text_info+1) % (GRAPH_DISPLAY_MODE_LOT_OF_TEXT+1) ; break;
                default: break;
            }
        } break;
        default: break;
    }

    return false;
}