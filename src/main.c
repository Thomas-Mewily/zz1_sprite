#include "base.h"
#include "test.h"

/*
gcc -fdiagnostics-color=always -g ./src/*.c -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o ./bin/main.exe
gcc -fdiagnostics-color=always -g ./src/*.c ./src/context/*.c ./src/util/*.c -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o ./bin/main.exe
gcc -fdiagnostics-color=always -g ./src/*.c ./src/context/*.c ./src/util/*.c ./src/collection/*.c -Iinclude -Llib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o ./bin/main.exe
./bin/main
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


void draw_triangle(context* c)
{
    //pen_triangle_colored(c, 10, 10, color_red, 10, 90, color_blue, 40, 60, color_green);
    int delta = 200;
    //pen_triangle_colored(c, 10, 10, color_red, 10, 10+delta, color_blue, 10+delta/2, delta*2/3, color_black);


    float x = c->screen_width/4;
    float y = c->screen_height/2;
    float step = c->screen_height/8;

    
    pen_goto(c, x-step, y+step);
    pen_color(c, color_white);

    pen_down(c);
        pen_goto(c, x+step, y+step);
        pen_color(c, color_red);

        pen_goto(c, x+step, y-step);
        pen_color(c, color_black);

        pen_goto(c, x-step, y-step);
        pen_color(c, color_blue);

        pen_goto(c, x-step, y+step);
        pen_color(c, color_white);
    pen_up(c);

    pen_goto(c, 0, 0);
}



int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    init();
    test_debug();

    context* c = context_create("Mini Engine. Thomas T", 960, 540, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    window_center_coef(c, 0.5, 0.5);

    bool stop = false;

    texture* t = texture_create(c, "asset/knight_ko.png");

    while (!stop)
    {
        context_update(c);

        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT: stop = true; break;
                /*
                

                case SDL_KEYDOWN:
                case SDL_KEYUP:
                {
                    #define speed 10
                    bool isPress = event.type == SDL_KEYDOWN;
                    switch (event.key.keysym.sym)
                    {
                        #define target(x, y) { target_x = x*(screen.w-window_width); target_y = (1-y)*(screen.h-window_height); need_target = true; } break;

                        case SDLK_7: case SDLK_KP_7: target(   0,   1); break;
                        case SDLK_8: case SDLK_KP_8: target( 0.5,   1); break;
                        case SDLK_9: case SDLK_KP_9: target(   1,   1); break;
                        case SDLK_4: case SDLK_KP_4: target(   0, 0.5); break;
                        case SDLK_5: case SDLK_KP_5: target( 0.5, 0.5); break;
                        case SDLK_6: case SDLK_KP_6: target(   1, 0.5); break;
                        case SDLK_1: case SDLK_KP_1: target(   0,   0); break;
                        case SDLK_2: case SDLK_KP_2: target( 0.5,   0); break;
                        case SDLK_3: case SDLK_KP_3: target(   1,   0); break;
                        
                        case SDLK_ESCAPE: stop = true; break;
                        case SDLK_SPACE: 
                        {
                            SDL_SetWindowPosition(window2, window_get_x(window), window_get_y(window));
                        }break;
  
                        case SDLK_RIGHT:  case SDLK_f:  window_move(window, +speed, 0     ); break;
                        case SDLK_LEFT :  case SDLK_s:  window_move(window, -speed, 0     ); break;
                        case SDLK_UP   :  case SDLK_e:  window_move(window,      0, +speed); break;
                        case SDLK_DOWN :  case SDLK_d:  window_move(window,      0, -speed); break;

                        case SDLK_F5: case SDLK_p: window_animation = !window_animation; break;
                        case SDLK_DELETE:
                        case SDLK_CLEAR:
                        case SDLK_CARET:
                            break;
                            
                        case SDLK_F11:
                            if(event.type == SDL_KEYDOWN)
                            { 
                                window_change_fullscreen(window);
                            }
                        break;
                            
                        default: break;
                    }
                } break;*/
                default: break;
            }
        }

        pen_mode(c, PEN_MODE_FILLED);
        //pen_color(c, color_white);
        pen_color(c, rgb(100, 30, 150));
        pen_clear(c);


        //float len = length(c->mouse_x, c->mouse_y, c->window_width/2, c->window_height/2);
        float lenX = abs(c->mouse_x-(float)c->window_width/2);
        float lenY = abs(c->mouse_y-(float)c->window_height/2);

        pen_color(c, rgb(255*c->mouse_x/(float)c->window_width, 255*c->mouse_y/(float)c->window_height, 127));
        pen_oval(c, c->window_width/4, c->window_height/2, lenX, lenY);

        pen_mode(c, PEN_MODE_HOLLOW);
        pen_color(c, hsv(360*lenX/(c->window_width/2), 1 , 1));
        pen_oval(c, c->window_width*3/4, c->window_height/2, lenY, lenX);



        pen_color(c, color_white);
        pen_line(c, c->window_width/2, c->window_height/2, c->mouse_x, c->mouse_y);

        draw_triangle(c);

        pen_texture(c, t, texture_rect(t), window_rectf(c));
        
        //draw_texture(c, t);

        //printf("%x\n", c->mouse_flag);

        context_draw(c);
    }


    unload(c);

    return 0;
}