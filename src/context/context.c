#include "base.h"

// void check_font_charged(TTF_Font* f)
// {
//     if (!f)
//     {
//         SDL_Log("Impossible d'ouvrir la police : %s\n", TTF_GetError());
//     }
// }

context* context_create(char* window_name, int width, int height, Uint32 flags)
{
    context* c = create(context);
    c->window = SDL_CreateWindow(window_name,
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            width,
                                            height,
                                            flags);
    if (c->window == NULL)
    {
        printf("Impossible de creer la fenetre: %s\n", SDL_GetError());
        return null;
    }

    c->renderer = SDL_CreateRenderer(c->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (c->renderer == NULL)
    {
        printf("Impossible de creer le renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(c->window);
        return null;
    }

    c->window_width = width;
    c->window_width = height;
    SDL_GetWindowSize(c->window, &c->window_width, &c->window_height);
    
    c->pen_x = 0;
    c->pen_y = 0;
    c->pen_scale = 1;
    c->pen_mode  = 2;
    c->pen_move_rotation = from_degree(0);
    c->_pen_is_down = false;

    repeat(i, 3)
    {
        c->_pen_vertex[i].tex_coord.x = 0;
        c->_pen_vertex[i].tex_coord.y = 0;
    }
    
    c->should_exit = false;
    c->scene = null;

    twice(context_update(c););


    // //Charge la font sous différentes tailles 
    // c->font_small           = TTF_OpenFont(FONT_PATH, 20); check_font_charged(c->font_small);
    // c->font_medium          = TTF_OpenFont(FONT_PATH, 30); check_font_charged(c->font_medium);
    // c->font_big             = TTF_OpenFont(FONT_PATH, 50); check_font_charged(c->font_big);
    // c->font_fullscreen      = TTF_OpenFont(FONT_PATH, 70); check_font_charged(c->font_fullscreen);

    return c;
}

void context_update(context* c)
{
    SDL_DisplayMode screen;
    SDL_GetCurrentDisplayMode(0, &screen);
    c->screen_width  = screen.w;
    c->screen_height = screen.h;

    SDL_GetWindowPosition(c->window, &c->window_x, &c->window_y);
    SDL_GetWindowSize(c->window, &c->window_width, &c->window_height);

    c->window_ratio_width_div_height = c->screen_width/(float)c->screen_height;
    c->window_ratio_height_div_width = c->screen_height/(float)c->screen_width;

    //printf("window %i %i, mouse %i %i\n", c->window_width, c->window_height, c->mouse_x, c->mouse_y);

    c->mouse_old_flag = c->mouse_flag;
    c->mouse_old_x = c->mouse_x;
    c->mouse_old_y = c->mouse_y;
    c->mouse_flag = SDL_GetMouseState(&(c->mouse_x), &(c->mouse_y));
    c->kb_state = SDL_GetKeyboardState(NULL);

    c->timer = from_ms(SDL_GetTicks());
    c->font = null;

    scene_update(c, (scene*)(c->scene));
}

void context_draw(context* c)
{
    scene_draw(c, (scene*)(c->scene));
    SDL_RenderPresent(c->renderer);
}

void contexte_free(context* c)
{
    // TTF_CloseFont(c->font_small);
    // TTF_CloseFont(c->font_medium);
    // TTF_CloseFont(c->font_big);
    // TTF_CloseFont(c->font_fullscreen);
    
    scene_unload(c, (scene*)(c->scene));
    SDL_DestroyRenderer(c->renderer);
    SDL_DestroyWindow(c->window);
}