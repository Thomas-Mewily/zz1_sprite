#include "base.h"

parallaxe* create_parallaxe(int max_depth)
{
    return null;
}

void get_parallaxe_at(context* c, int time)
{
    return;
}

void free_parallaxe(parallaxe* p)
{
    for (int i = 0; i < p->max_depth; i++)
    {
        SDL_DestroyTexture(p->layers[i]);
    }
    free(p->layers);
    free(p);
}