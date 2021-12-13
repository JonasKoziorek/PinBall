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
    SDL_Rect rect;
    FlipperSide side;
    FlipperState state;
    float angle;
}Flipper;

void ComputeFlipperVerts(float width, float height,cpVect *verts, FlipperSide side);

Flipper* InitFlipper(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height, FlipperSide side);

void PrintFlipper( cpSpace *space, SDL_Renderer *renderer, Flipper *flip, SDL_Texture *texture);

void FlipperMove( cpSpace *space, Flipper *flip, cpFloat timeStep );

void DeleteFlipper( cpSpace *space, Flipper *flip );

