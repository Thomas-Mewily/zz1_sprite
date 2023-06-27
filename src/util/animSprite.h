#ifndef ANIMSPRITE
#define ANIMSPRITE
#include "base.h"

struct sprite_sheet;
typedef struct sprite_sheet sprite_sheet;

struct sprite_sheet{
    SDL_Texture* sprite_sheet;
    SDL_Rect* lst_frame;
    int frame_count;
    int frame_width;//taille d'une frame (constante)
    int frame_height;
    int width;//taille de la texture totale
    int height;
};

struct animation;
typedef struct animation animation;
typedef animation anim;

struct animation{
    sprite_sheet* sprite_sheet;
    int frame_duration;//temps d'une image en millisecondes
    int first_frame;
    int last_frame;
    bool loop;
};

sprite_sheet* create_sprite_sheet(context* c,const char* filename, int w, int h);

animation* create_animation(sprite_sheet* sprite_sheet, int* lstFrame, bool loop);

void get_frame(animation* s);


#endif