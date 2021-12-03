#pragma once
#include "Chipmunk/include/chipmunk/chipmunk.h"
#include "SDL2/SDL_image.h"
#include "Img.h"

typedef enum{
    SlingSideLeft,
    SlingSideRight
}SlingSide;

typedef struct{
    cpBody *body;
    cpShape *shape;
    Img img;
    SlingSide type;
}Slingshot;

Slingshot* InitSlingshot(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height, SlingSide type, const char *path );

void PrintSlingshot( SDL_Renderer *renderer, Slingshot *sling );

void DeleteSlingshot( Slingshot *sling );
