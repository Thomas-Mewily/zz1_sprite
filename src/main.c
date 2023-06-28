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
    
    // if(TTF_Init()==-1) {
    //     printf("Impossible d'initialiser la SDL TTF\n");
    //     crash(TTF_GetError());
    // }
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

    scene_set(c, titre);
    //scene_set(c, houza);
    //scene_set(c, thomas_parallax);

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