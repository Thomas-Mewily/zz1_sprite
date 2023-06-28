#ifndef CONTEXT_SCENE_H
#define CONTEXT_SCENE_H
#include "base.h"

#define scene_name_max_length 256

struct scene_struct;
typedef struct scene_struct scene;

typedef void (*scene_fn)(context* c, scene* sce);

typedef struct
{
   color background_color;
   void* argument;

   time time;              // since the beginning of the scene
   time time_when_active;  // based on context.time

   bool active;
   bool is_loaded;
   char name[scene_name_max_length];

   #define scene_fn(name) void (*name)(context* c, scene* sce)

   scene_fn load;
   scene_fn unload;

   scene_fn update;
   scene_fn draw;

   scene_fn printf;

} scene_info;

struct scene_struct
{
   scene_info info;
   void* state;
};

scene* scene_create_arg(char name[256], scene_fn load, scene_fn unload, scene_fn update, scene_fn draw, scene_fn printf, void* argument);

void scene_unload(context* c, scene* sce);
void scene_update(context* c, scene* sce);
void scene_draw  (context* c, scene* sce);
void scene_printf(context* c, scene* sce);

#define scene_create(name) scene_create_arg(#name "\0",  \
   scene_ ## name ## _load,\
   scene_ ## name ## _unload,\
   scene_ ## name ## _update,\
   scene_ ## name ## _draw,  \
   scene_ ## name ## _printf,\
   null\
)

void scene_switch(context* c, scene* sce);

void scene_set_active(context* c, scene* sce);
void scene_set_inactive(context* c, scene* sce);

#define scene_set(context, name) scene_switch(context, scene_create(name))

#endif