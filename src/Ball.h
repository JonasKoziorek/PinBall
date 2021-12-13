#pragma once
#include "Chipmunk/include/chipmunk/chipmunk.h"
#include "SDL2/SDL_image.h"
#include "Img.h"
#include "stdbool.h"

typedef struct{
    cpBody *body;
    cpShape *shape;
    Img img;
    bool ingame;
}Ball;

Ball* InitBumper(cpSpace *space, SDL_Renderer *renderer, cpVect pos, cpVect vel, float radius, const char *path);

Ball* InitBall(cpSpace *space, SDL_Renderer *renderer, cpVect pos, cpVect vel, float radius, const char *path);

void PrintBall( SDL_Renderer *renderer, Ball *ball );

void DeleteBall( cpSpace *space, Ball *ball );

void DeleteBumper( cpSpace *space, Ball *ball );
