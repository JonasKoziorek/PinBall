#pragma once
#include "Chipmunk/include/chipmunk/chipmunk.h"
#include "SDL2/SDL_image.h"
#include "Img.h"
#include <stdbool.h>

typedef struct{
    cpBody *body;
    cpShape *shape;
    Img img;
}Box;

Box* InitBox(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height, const char *path );

void PrintBox( SDL_Renderer *renderer, Box *box );

void DeleteBox( Box *box );
