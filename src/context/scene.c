#include "base.h"

scene* scene_create_arg(char name[256], scene_fn load, scene_fn unload, scene_fn update, scene_fn draw, scene_fn printf, void* argument)
{
    scene* sce = create(scene);
    scene_info* i = &sce->info;

    i->active = true;

    i->argument = null;

    i->background_color = color_black;
    repeat(k, scene_name_max_length)
    {
        i->name[k] = name[k];
    }
    i->name[scene_name_max_length-1] = '\0'; // just to be sure

    i->load = load;
    i->unload = unload;
    i->update = update;
    i->draw = draw;
    i->printf = printf;

    i->is_loaded = false;

    sce->state = null;

    return sce;
}

void scene_unload(context* c, scene* sce)
{
    if(sce == null) return;

    if(sce->info.active) { scene_set_inactive(c, sce); }

    sce->info.unload(c, sce);
    free(sce->info.argument);
    free(sce);
}

void scene_update(context* c, scene* sce)
{
    if(sce == null) return;
    sce->info.time = c->timer - sce->info.time_when_active;
    sce->info.update(c, sce);
}

void scene_draw(context* c, scene* sce)
{
    if(sce == null) return;
    color co = pen_get_color(c);
    pen_color(c, sce->info.background_color);
    pen_clear(c);
    pen_color(c, co);
    sce->info.draw(c, sce);
}

void scene_printf(context* c, scene* sce)
{
    if(sce == null) return;
    printf("scene %s:\n", sce->info.name);
    sce->info.printf(c, sce);
    printf("\n");
}

void scene_set_active(context* c, scene* sce)
{
    if(sce == null) { return;}
    if(sce->info.is_loaded == false)
    {
        sce->info.is_loaded = true;
        sce->info.load(c, sce);
    }
    printf("scene %s active\n", sce->info.name);
    sce->info.active = true;
}
void scene_set_inactive(context* c, scene* sce)
{
    if(sce == null) { return;}
    sce->info.active = false;
}

void scene_switch(context* c, scene* sce)
{
    scene_unload(c, c->scene);
    c->scene = sce;
    if(sce)
    {
        scene_set_active(c, sce);
        sce->info.time_when_active = c->timer;
    }
}