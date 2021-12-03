#pragma once
#include "Chipmunk/include/chipmunk/chipmunk.h"
#include "SDL2/SDL_image.h"
#include "Img.h"
#include "stdbool.h"

typedef enum{
    FlipperMovingUp, 
    FlipperMovingDown,
    FlipperNotMoving
}FlipperState;

typedef enum{
    FlipperSideLeft,
    FlipperSideRight
}FlipperSide;

typedef struct{
    cpBody *body;
    cpShape *shape;
    Img img;
    FlipperSide side;
    FlipperState state;
}Flipper;

Flipper* InitFlipper(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height, const char *path, FlipperSide side);

void PrintFlipper( cpSpace *space, SDL_Renderer *renderer, Flipper *flip );

void FlipperMove( cpSpace *space, Flipper *flip );

void DeleteFlipper( Flipper *flip );

