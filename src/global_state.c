#include "base.h"

#define FPS_IDLE 500
#define FPS_WALK 200

/*
no opti, fast compile : -O0
lot of opti, slow compile : -O4

gcc -O4 -fdiagnostics-color=always -g ./src/*.c ./src/context/*.c ./src/util/*.c ./src/collection/*.c ./src/scene/*.c ./src/graph/*.c -Wall -Wextra -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o ./bin/main.exe
gcc -O0 -fdiagnostics-color=always -g ./src/*.c ./src/context/*.c ./src/util/*.c ./src/collection/*.c ./src/scene/*.c ./src/graph/*.c -Wall -Wextra -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o ./bin/main.exe
./bin/main.exe
gource
*/

void get_graph(context* c)
{
    if(gs->g != null)
    {
        graph_free(gs->g);
    }

    //gs->g = graph_generate(200, rectanglef(0, 0, 160, 90), 0.25f);
    //gs->g = graph_generate(100, rectanglef(0, 0, 160, 90), 0.25f);
    //gs->g = graph_generate( 8, rectanglef(0, 0, 16, 9), 0.25f);
    gs->g = graph_generate( 3+(rand()%10), rectanglef(0, 0, 16*4, 9*4), 0.25f);
    graph_change_distances(gs->g);
    //gs->g = graph_complet(8);

    if(gs->goblin_traveler != null)
    {
        traveler_free(gs->goblin_traveler);
    }

    gs->goblin_traveler = traveler_create(gs->g, length(0,0,gs->g->x_etendu,gs->g->y_etendu)/1.0);
    traveler_travel_node(gs->goblin_traveler, 0);

}

void global_state_load(context* c)
{
    gs = create(the_global_state);
    gs->g = null;
    gs->goblin_traveler = null;
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

    /*
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
    gs->goblin_anim_left_idle->last_frame = 7; */

    gs->gobelin_texture = texture_create(c, "asset/gobelin.png");


    gs->diamant = sprite_sheet_create(c, "asset/diamant.png", 16, 16);
    gs->diamant_anim = animation_create(gs->diamant, frequence_s(16));
}

void global_state_unload(context* c)
{
    /*
    free_animation(gs->goblin_anim_down_walk);
    free_animation(gs->goblin_anim_right_walk);
    free_animation(gs->goblin_anim_up_walk);
    free_animation(gs->goblin_anim_left_walk);

    free_animation(gs->goblin_anim_down_idle);
    free_animation(gs->goblin_anim_right_idle);
    free_animation(gs->goblin_anim_up_idle);
    free_animation(gs->goblin_anim_left_idle);
    sprite_sheet_free(gs->goblinS);
    */

    texture_free(gs->gobelin_texture);
    sprite_sheet_free(gs->diamant);
    animation_free(gs->diamant_anim);
    graph_free(gs->g);

    traveler_free(gs->goblin_traveler);
    free(gs);
}

void global_state_update(context* c)
{
    gs->g->draw_dest = window_rectf(c);
    
    traveler_update(c, gs->goblin_traveler);
    //printf("%i\n", (int)as_degree(gs->goblin_traveler->direction));
    //printf("%i\n", (int)traveler_time(gs->goblin_traveler));
    /*
    if(c->nb_update % 10)
    {
        printf("%.3f, %.3f\n", camera_pixel_pos_2_graph_pos_x(c, gs->g, input_mouse_x(c)),
                                              camera_pixel_pos_2_graph_pos_y(c, gs->g, input_mouse_y(c))
                                              );
    }*/
}

int direction_to_gobelin_animation(angle a)
{
    // bidouille
    float x = cos(a);
    float y = sin(a);
    if(abs(x) > abs(y))
    {
        if(x > 0) return 2;
        return 3;
    }
    if(y > 0) return 0;
    return 1;
}

void global_state_draw(context* c)
{
    pen_graph(c, gs->g);
    
    if(gs->g->draw_text_info == GRAPH_DISPLAY_MODE_GRAPHIC)
    {
        graph* g = gs->g;
        traveler* t = gs->goblin_traveler;

        int is_base_anim = t->state == TRAVELER_STATE_WAIT_TO_WALK;
        int nb_frame = is_base_anim ? 2 : 4;
        int frame_fps = is_base_anim ? 3 : 8;
        int direction = direction_to_gobelin_animation(t->direction);

        rect src = rectangle(traveler_time(t) / (frequence_s(frame_fps)) % nb_frame * 24,
                        (4*(is_base_anim?0:1)+direction)*32,24,32);
        pen_texture_at_center(c, gs->gobelin_texture, src, camera_graph2cam_x(c,g,t->x), camera_graph2cam_y(c,g,t->y), 3, 3, 0.5, 0.5);
    
        pen_draw_trajet(c, gs->g, gs->goblin_traveler->chemin);


        // Cancel camera zoom
        camera_state cs = camera_get_state(c);
        camera_set_state(c, camera_state_default());
        // Not affected by scrolling or scalling
        pen_formatted_text_at_center(c, 0, 0, FONT_SIZE_NORMAL, 0, 0, "Temps : %.1f", gs->goblin_traveler->total_distance_traveled);
        camera_set_state(c, cs);
    }



    //if(traveler_can_travel(t))
    
    //pen_animation_at_center(c, gs->gobelin_texture, window_width(c)/2, window_height(c)/2, 4,4, 0.5, 0.5, timer_since_launch(c));
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
                case SDLK_g: gs->g->draw_text_info = (gs->g->draw_text_info+1) % GRAPH_DISPLAY_MODE_MODULO ; break;
                default: break;
            }
        } break;
        case SDL_MOUSEBUTTONDOWN:
        {
            node* n = graph_get_node_touched_by_mouse(c, gs->g);
            if(n != null)
            {
                traveler_travel_node(gs->goblin_traveler, n->idx);
            }
            return true;
        }   
        break;
        default: break;
    }

    return false;
}