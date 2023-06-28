#ifndef THE_CONTEXT_H
#define THE_CONTEXT_H
#include "base.h"

#define FONT_PATH "asset/Milky Mania.ttf"
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

    float  _camera_x;
    float  _camera_y;
    float  _camera_scale_x;
    float  _camera_scale_y;
    bool   _camera_can_zoom;
    bool   _camera_can_scroll;

    uint32 pen_mode;
    //angle  pen_move_rotation;
    //bool   _pen_is_down;
    //vertex _pen_vertex[3];
    //int    _pen_idx;

    bool should_exit;

    //TTF_Font* font_small;
    //TTF_Font* font_medium;
    //TTF_Font* font_big;
    //TTF_Font* font_fullscreen;
    texture* _pen_font;
} context;
#endif