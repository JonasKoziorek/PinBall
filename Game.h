#pragma once
#include "Chipmunk/include/chipmunk/chipmunk.h"
#include "Frame.h"

// kind of a garbage class which stores all commonly used structs needed everywhere

typedef struct{
    Frame frame;
    SDL_Window *window;
    SDL_Renderer *renderer;
    cpSpace *space;
}Game;

Game* InitGame();

void DeleteGame();
