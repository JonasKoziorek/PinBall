#pragma once
#include <SDL2/SDL_render.h>

typedef struct{
    int width;
    int height;
}Frame;

void DrawFrame( Frame *frame, SDL_Renderer *renderer );

