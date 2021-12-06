#pragma once
#include "Chipmunk/include/chipmunk/chipmunk.h"
#include "Frame.h"
#include "Box.h"
#include "Flipper.h"
#include "Curve.h"
#include "Slingshot.h"
#include "Spring.h"

/*
    Map structure unifies all the static objects under one structure.
    Map.c/Map.h provide functions to initialize Map struct, freeing allocated memory and printing object on sdl window.
    There are several static objects:
        Walls
            Serve only as borders of the sdl window and are invisible in the game.
        Boxes
            Rectangular shapes. 
        Curves
            Curved (ellipse-like) shapes.
        Flippers
            Movable objects on the bottom of the sdl window. They bounce the ball off.
        Slingshots
            Slingshots are polygon shapes.
*/

typedef struct{
    cpShape **arr;
    int len;
}Walls;

typedef struct{
    Box **arr;
    int len;
    SDL_Texture *texture;
}Boxes;

typedef struct{
    Flipper *arr[2];
    SDL_Texture *texture;
}Flippers;

typedef struct{
    Curve **arr;
    int len;
    SDL_Texture *texture;
}Curves;

typedef struct{
    Slingshot **arr;
    int len;
    SDL_Texture *texture;
}Slings;

typedef struct{
    Spring **arr;
    int len;
    SDL_Texture *texture;
}Springs;

typedef struct{
    Walls walls;
    Boxes boxes; 
    Flippers flips;
    Curves curves;
    Slings slings;
    Springs springs;
    cpFloat fri;
    cpFloat ela;
}Map;

void MapSetObjectFriEla( cpShape *shape, cpFloat fri, cpFloat ela );

void SetupWall(Map *map, cpSpace *space, int i, cpVect p1, cpVect p2 );

void SetupWalls( cpSpace *space, Map *map, const int len, Frame frame );

void SetupBoxes( cpSpace *space, Map *map, const int len, SDL_Renderer *renderer, const char *path);

void SetupFlippers( cpSpace *space, SDL_Renderer *renderer , Map *map, const char *path);

void SetupCurves( cpSpace *space, Map *map, const int len, SDL_Renderer *renderer, const char *path);

void SetupSlingshots( Map *map, cpSpace *space, SDL_Renderer *renderer, int len, const char *path);

void PrintMap( cpSpace *space, SDL_Renderer *renderer, Map *map );

Map* InitMap( cpSpace *space, Frame frame, SDL_Renderer *renderer);
    
void DestroyMap( cpSpace *space, Map *map );
