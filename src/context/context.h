#ifndef THE_CONTEXT_H
#define THE_CONTEXT_H
#include "base.h"

typedef struct
{
    int screen_width;
    int screen_height;

    SDL_Window* window;
    int window_width;
    int window_height;

    int window_x;
    int window_y;

    SDL_Renderer* renderer;

    int mouse_x;
    int mouse_y;
    int32 mouse_flag;

    Uint8* kb_state;

    timer tick;

    float  pen_x;
    float  pen_y;
    float  pen_scale;
    uint32 pen_mode;
    angle  pen_move_rotation;
    bool   _pen_is_down;
    vertex _pen_vertex[3];
    int    _pen_idx;

} context;

context* context_create(char* window_name, int width, int height, Uint32 flags);
void context_update(context* c);
void context_draw(context* c);
void contexte_free(context* c);
#endif