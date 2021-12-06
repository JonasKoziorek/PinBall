#pragma once
#include "Chipmunk/include/chipmunk/chipmunk.h"
#include "SDL2/SDL_image.h"

typedef struct{
    cpBody *body;
    cpShape *shape;
    SDL_Rect rect;
}Box;

Box* InitBox(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height);

void PrintBox( SDL_Renderer *renderer, Box *box, SDL_Texture *texture);

void DeleteBox( cpSpace *space, Box *box );
