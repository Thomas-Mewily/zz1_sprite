#ifndef THE_CONTEXT_H
#define THE_CONTEXT_H
#include "base.h"

//extern struct scene_struct;
typedef struct
{
    int screen_width;
    int screen_height;

    float window_ratio_width_div_height;
    float window_ratio_height_div_width;

    SDL_Window* window;
    int window_width;
    int window_height;

    int window_x;
    int window_y;

    SDL_Renderer* renderer;

    int mouse_x;
    int mouse_y;
    int32 mouse_flag;

    int mouse_old_x;
    int mouse_old_y;
    int32 mouse_old_flag;
    const Uint8* kb_state;

    time timer; // since the beginning of the program

    void* scene;

    float  pen_x;
    float  pen_y;
    float  pen_scale;
    uint32 pen_mode;
    angle  pen_move_rotation;
    bool   _pen_is_down;
    vertex _pen_vertex[3];
    int    _pen_idx;

    bool should_exit;
} context;

context* context_create(char* window_name, int width, int height, Uint32 flags);
void context_update(context* c);
void context_draw(context* c);
void contexte_free(context* c);
#endif