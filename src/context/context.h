#ifndef THE_CONTEXT_LOADER_H
#define THE_CONTEXT_LOADER_H
#include "base.h"

context* context_create(char* window_name, int width, int height, Uint32 flags);
void context_update(context* c);
void context_draw(context* c);
void contexte_free(context* c);

#endif