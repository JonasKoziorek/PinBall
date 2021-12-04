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
    SDL_Rect rect;
    CurveRot rot;
    int precision;
}Curve;

void ShowCurvature(SDL_Renderer *renderer, Curve *curve);

Curve* InitCurve(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height, CurveRot rot );

void ComputeCurve( int count, cpVect *verts, float width, float height, CurveRot rot);

void PrintCurve( SDL_Renderer *renderer, Curve *curve, SDL_Texture *texture );

void DeleteCurve( cpSpace *space, Curve *curve );
