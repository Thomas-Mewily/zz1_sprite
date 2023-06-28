/*
#ifndef PARALLAXE
#define PARALLAXE
#include "base.h"



struct parallaxe;
typedef struct parallaxe parallaxe;

struct parallaxe{
    SDL_Texture** layers;
    int max_depth;
};

parallaxe* create_parallaxe(int max_depth);

void get_parallaxe_at(context* c, int time);

void free_parallaxe(parallaxe* p);

#endif*/