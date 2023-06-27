#include "base.h"

sprite_sheet* create_sprite_sheet(context* c, const char* filename, int w, int h)
{
    sprite_sheet* newSS = create(sprite_sheet);
    SDL_Surface* CD = IMG_Load(filename);
    newSS->sprite_sheet = SDL_CreateTextureFromSurface(c->renderer,CD);

    newSS->frame_count = CD->w / w;
    newSS->frame_width = w;
    newSS->frame_height = h;

    newSS->width = CD->w;
    newSS->height = CD->h;

    newSS->lst_frame = create(SDL_Rect);
    for (int i = 0; i < newSS->frame_count; i++)
    {
        SDL_Rect rect;
        rect.x = i * w;
        rect.y = 0;
        rect.w = w;
        rect.h = h;

        newSS->lst_frame[i] = rect;
    }

    SDL_FreeSurface(CD);
    return newSS;
}

animation* create_animation(sprite_sheet* sprite_sheet, int* lst_frame, bool loop)
{
    animation* newAS = create(animation);
}

void get_frame(animation* s)
{

}