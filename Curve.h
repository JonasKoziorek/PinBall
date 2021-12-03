#pragma once
#include "Chipmunk/include/chipmunk/chipmunk.h"
#include "SDL2/SDL_image.h"
#include "Img.h"

typedef enum{
    CurveRotSW, CurveRotSE, CurveRotNW, CurveRotNE
}CurveRot;

typedef struct{
    cpBody *body;
    cpShape *shape;
    Img img;
    CurveRot rot;
    int precision;
}Curve;

void ShowCurvature(SDL_Renderer *renderer, Curve *curve);

Curve* InitCurve(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height, CurveRot rot, const char *path );

void ComputeCurve( int count, cpVect *verts, float width, float height, CurveRot rot);

void PrintCurve( SDL_Renderer *renderer, Curve *curve );

void DeleteCurve( Curve *curve );
