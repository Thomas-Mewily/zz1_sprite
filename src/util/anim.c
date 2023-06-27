#include "base.h"


anim* animation_create(sprite_sheet* sprite_sheet, timer frame_duration)
{
    animation* newAS = create(animation);
    newAS->first_frame = 0;
    newAS->last_frame = (sprite_sheet->frame_count-1);
    newAS->nb_frame = newAS->last_frame-newAS->first_frame+1;
    newAS->frame_duration = frame_duration;
    newAS->sprite_sheet = sprite_sheet;
    newAS->loop = true;
    return newAS;
}

void animation_free(animation* a)
{
    free(a);
}

rect* animation_get_frame(animation* a, timer t)
{
    int frame_number = t / a->frame_duration - a->first_frame;
    int frame_id;
    if (a->loop)
    {
        frame_id = frame_number % a->nb_frame;
    }
    else
    {
        frame_id = frame_number > a->nb_frame;
    }
    return &(a->sprite_sheet->frames[frame_id]);
}