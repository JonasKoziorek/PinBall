#pragma once
#include "Chipmunk/include/chipmunk/chipmunk.h"
#include "SDL2/SDL_image.h"

typedef enum{
    SlingSideLeft,
    SlingSideRight
}SlingSide;

typedef struct{
    cpBody *body;
    cpShape *shape;
    SDL_Rect rect;
    SlingSide type;
}Slingshot;

Slingshot* InitSlingshot(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height, SlingSide type );

void PrintSlingshot( SDL_Renderer *renderer, Slingshot *sling, SDL_Texture *texture );

void DeleteSlingshot( cpSpace *space, Slingshot *sling );
