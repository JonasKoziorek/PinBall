#pragma once
#include "Ball.h"
#include "Frame.h"

typedef struct{
    Ball** arr;
    int len;
}BallArr;

BallArr* InitBallArr(cpSpace *space, SDL_Renderer *renderer, int len);

void PrintBallArr( SDL_Renderer *renderer, BallArr *ballarr );

bool CheckGameStatus( BallArr *ballarr );

void CheckInGameBalls(Frame *frame, BallArr *ballarr );

void DestroyBallArr( BallArr *ballarr);
