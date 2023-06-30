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

void global_state_reset_traveler(context* c)
{
    if(gs->goblin_traveler != null)
    {
        traveler_free(gs->goblin_traveler);
    }
    gs->goblin_traveler = traveler_create(gs->g, gs->g->rectangle_length*2.0);
    traveler_travel_node(gs->goblin_traveler, 0, false);
    if(gs->g != null)
    {
        repeat(i, graph_get_nb_node(gs->g)-1)
        {
            graph_get_node(gs->g, i+1)->etat = node_a_visiter;
        }
    }
}

void global_state_new_get_graph(context* c)
{
    if(gs->g != null)
    {
        graph_free(gs->g);
    }

    /*
    gs->g = graph_empty();

    graph* g = gs->g;
    
    int a = graph_add_node_x_y(g, 0,  0);
    int b = graph_add_node_x_y(g, 1,  0);
    int x = graph_add_node_x_y(g, 1, -1);
    //int y = graph_add_node_x_y(g, 0.7, -2);
    //int z = graph_add_node_x_y(g, 1.5, -1.5);
    graph_add_join(g, a, b);
    graph_add_join(g, b, x);
    //graph_add_join(g, x, y);
    //graph_add_join(g, y, z);
    //graph_add_join(g, z, x);
    */
    //gs->g = graph_generate(200, rectanglef(0, 0, 160, 90), 0.25f);
    //gs->g = graph_generate(100, rectanglef(0, 0, 160, 90), 0.25f);
    //gs->g = graph_generate( 3, rectanglef(0, 0, 16, 9), 0.25f);
    gs->g = graph_generate( gs->nb_node, rectanglef(0, 0, sqrt(gs->nb_node)*16, sqrt(gs->nb_node)*9), 0.25f);
    graph_change_distances(gs->g);
    //gs->g = graph_complet(8);
    global_state_reset_traveler(c);
}

void global_state_load(context* c)
{
    gs = create(the_global_state);
    gs->nb_node = 6;
    gs->g = null;
    gs->goblin_traveler = null;
    //get_graph(c);
    gs->path_rs = vec_empty(int);
    global_state_new_get_graph(c);
    gs->longueur_rs = 10E10;

    


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
    
    //traveler_update(c, gs->goblin_traveler);
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


void global_state_draw(context* c)
{
    UNUSED(c);
    //pen_graph(c, gs->g);
}

void global_state_printf(context* c)
{
    global_state_new_get_graph(c);
}

bool global_state_event(context* c, event* ev)
{
    
    switch (ev->type)
    {
        //mousePress(ev->button.);
        case SDL_KEYDOWN: //case SDL_KEYUP:
        {
            switch (ev->key.keysym.sym)
            {
                case SDLK_ESCAPE: c->should_exit = true; break;
                case SDLK_m: scene_set(c, martin); return true;
                case SDLK_t: scene_set(c, thomas_parallax); return true;
                case SDLK_h: scene_set(c, houza); return true;
                case SDLK_j: scene_set(c, graph_joueur); gs->g->draw_text_info = GRAPH_DISPLAY_MODE_GRAPHIC; return true;
                case SDLK_f: scene_set(c, fourmi); return true;
                case SDLK_g: gs->g->draw_text_info = (gs->g->draw_text_info+1) % GRAPH_DISPLAY_MODE_MODULO ; return true;
                case SDLK_UP: case SDLK_RIGHT: gs->nb_node++; return true;
                case SDLK_DOWN: case SDLK_LEFT: gs->nb_node = gs->nb_node <= 2 ? 2 : gs->nb_node-1; return true;

                case SDLK_r: global_state_reset_traveler(c); return true;
                
                // Debug
                case SDLK_d: 
                    scene_printf(c, (scene*)(c->scene));
                    global_state_new_get_graph(c);
                return true;
                // menu Principal
                case SDLK_p: scene_set(c, titre); return true;
                default: break;
            }
        } break;
        default: break;
    }

    return false;
}