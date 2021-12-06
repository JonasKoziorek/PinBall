#pragma once
#include "Chipmunk/include/chipmunk/chipmunk.h"
#include "SDL2/SDL_image.h"

typedef enum{
    SpringMovingUp,
    SpringMovingDown,
    SpringIdle
}SpringState;

typedef struct{
    cpBody *body;
    cpShape *shape;
    SDL_Rect rect;
    SpringState state;
}Spring;

Spring* InitSpring(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height);

void PrintSpring( SDL_Renderer *renderer, Spring *spring, SDL_Texture *texture);

void DeleteSpring( cpSpace *space, Spring *spring );

void SpringMove(  Spring *spring );
