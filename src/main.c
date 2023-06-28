#include "base.h"
#include "test.h"

/*
no opti, fast compile : -O0
lot of opti, slow compile : -O4

gcc -O0 -fdiagnostics-color=always -g ./src/*.c ./src/context/*.c ./src/util/*.c ./src/collection/*.c ./src/scene/*.c -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o ./bin/main.exe
./bin/main.exe

*/

void init()
{
    printf("Compilation de %s\n", current_time);
    SDL_version nb;
    SDL_VERSION(&nb);
    printf("Version de la SDL : %d.%d.%d\n", nb.major, nb.minor, nb.patch);

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("Impossible d'initialiser la SDL\n");
        crash(SDL_GetError());
    }
}

void unload()
{
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    init();
    test_debug();

    context* c = context_create("Houzayfa M, Martin J, Thomas T. Version de " current_time, 960, 540, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    window_center_coef(c, 0.5, 0.5);

    //scene_set(c, titre);
    scene_set(c, thomas_parallax);

    while (!c->should_exit)
    {
        context_update(c);

        SDL_Event event;

        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT: c->should_exit = true; break;
                
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE: c->should_exit = true; break;
                        default: break;
                    }
                } break;
                default: break;
            }
        }

        context_draw(c);
    }

    contexte_free(c);
    unload();

    /*
    context* c = context_create("Espace pour tomber. Thomas T", 960, 540, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    window_center_coef(c, 0.5, 0.5);

    bool stop = false;

    //texture* t = texture_create(c, "asset/knight_ko.png");

    #define nb_parallax 4
    #define load_parallax(idx) texture_create(c, "asset/parallax" #idx ".png")

    texture* parallax[4] =
    {
        load_parallax(1),
        load_parallax(2),
        load_parallax(3),
        load_parallax(4),
    };

    sprite_sheet* ss = sprite_sheet_create(c, "asset/knight_ko.png", 24, 32);
    anim* knight = animation_create(ss, frequence_s(10));
    float time_s_offset = 0;

    while (!stop)
    {
        context_update(c);

        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT: stop = true; break;
                
                case SDL_KEYDOWN:
                case SDL_KEYUP:
                {
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE: stop = true; break;
                        case SDLK_SPACE: 
                        {
                            time_s_offset = c->timer_s;
                        }break;
                        default: break;
                    }
                } break;
                default: break;
            }
        }

        pen_color(c, color_black);
        pen_clear(c);
        
        float mX = -(c->mouse_x - (float)c->window_width /2)/(c->window_width /2);
        float mY = -(c->mouse_y - (float)c->window_height/2)/(c->window_height/2);

        float hole_x;
        float hole_y;
        for(int i = nb_parallax-1; i >= 0; i--)
        {
            float j = (i-((nb_parallax-1)/2.0))/((nb_parallax-1)/2.0);
            float dest_x = c->window_width /2 + mX*(j)*c->window_height/8;
            float dest_y = c->window_height/2 + mY*(j)*c->window_height/8;
            texture* t = parallax[i];
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

        int knight_anim_height = animation_height(knight);
        float scaleY = (int)(1.0/knight_anim_height*c->window_height/8);
        float timer = c->timer_s-time_s_offset;
        float fall_scale = scaleY+scaleY*abs(sin(timer*2*pi/4))*8/(timer*timer);
        pen_animation_at_center(c, knight, hole_x, hole_y, fall_scale, fall_scale, 0.5, 0.5, c->tick);

        //pen_animation()
        //pen_texture(c, t, texture_rect(t), window_rectf(c));
        
        //draw_texture(c, t);

        //printf("%x\n", c->mouse_flag);

        context_draw(c);
    }

    repeat(i, nb_parallax)
    {
        texture_free(parallax[i]);
    }

    sprite_sheet_free(ss);
    animation_free(knight);

    //texture_free(t);

    unload(c);*/

    return 0;
}

/*

gcc -fdiagnostics-color=always -g ./src/*.c ./src/context/*.c ./src/util/*.c ./src/collection/*.c ./src/scene/*.c -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o ./bin/main.exe
gcc -O0 -fdiagnostics-color=always -g ./src/*.c ./src/context/*.c ./src/util/*.c ./src/collection/*.c ./src/scene/*.c -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o ./bin/main.exe
gcc -fdiagnostics-color=always -g ./src/*.c ./src/context/*.c ./src/util/*.c ./src/collection/*.c ./src/scene/*.c -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o ./bin/main.exe
./bin/main

gcc -x c-header -H -o ./src/base.h.gch ./src/base.h
gcc -x c-header -H -o base.h.gch ./src/base.h
*/