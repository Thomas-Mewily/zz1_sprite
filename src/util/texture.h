#ifndef TEXTURE_H
#define TEXTURE_H
#include "base.h"

typedef SDL_Texture texture;
int texture_width(texture* t);
int texture_height(texture* t);

texture* texture_create(context* c, char *path);
void texture_unload(texture* t);

rect texture_rect(texture* t);
rectf texture_rectf(texture* t);


#endif