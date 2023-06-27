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

animation* create_animation(sprite_sheet* sprite_sheet)
{
    animation* newAS = create(animation);
    newAS->first_frame = 0;
    newAS->last_frame = sprite_sheet->frame_count-1;
    newAS->frame_duration = 100;
    newAS->sprite_sheet = sprite_sheet;
    newAS->loop = true;
}

SDL_Rect* get_frame(animation* a, int time)
{
    int frame_number = time / a->frame_duration - a->first_frame;
    int frame_id;
    if (a->loop)
    {
        frame_id = frame_number % (a->last_frame - a->first_frame);
    }
    else
    {
        frame_id = frame_number > a->last_frame ? a->last_frame : frame_number;
    }
    return a->sprite_sheet->lst_frame[frame_id];
}
