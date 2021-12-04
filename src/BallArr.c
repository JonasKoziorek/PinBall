#include "BallArr.h"

BallArr* InitBallArr(cpSpace *space, SDL_Renderer *renderer,int len){
    len += 3;
    BallArr* ballarr = (BallArr*)malloc( sizeof(BallArr) );
    Ball** arr = (Ball**)malloc( sizeof(Ball*) * len);
    ballarr->len = len;
    ballarr->arr = arr;
    ballarr->arr[0]  = InitBall(space, renderer, cpv(15, -450), cpv(10, 10), 15, "images/pinball.png");
    ballarr->arr[1]  = InitBall(space, renderer, cpv(685, -450), cpv(10, 10), 15, "images/pinball.png");

    ballarr->arr[ballarr->len-3]  = InitBumper(space, renderer, cpv(235, -200), cpv(0, 0), 40, "images/linux.png");
    ballarr->arr[ballarr->len-2]  = InitBumper(space, renderer, cpv(350, -350), cpv(0, 0), 40, "images/linux.png");
    ballarr->arr[ballarr->len-1]  = InitBumper(space, renderer, cpv(465, -200), cpv(0, 0), 40, "images/linux.png");

    return ballarr;
}

void PrintBallArr( SDL_Renderer *renderer, BallArr* ballarr ){
    for( int i = 0; i < ballarr->len; i++ ){
        cpVect pos = cpBodyGetPosition(ballarr->arr[i]->body);
        ballarr->arr[i]->img.rect.x = pos.x - cpCircleShapeGetRadius(ballarr->arr[i]->shape);
        ballarr->arr[i]->img.rect.y = -pos.y - cpCircleShapeGetRadius(ballarr->arr[i]->shape);
        SDL_RenderCopy(renderer, ballarr->arr[i]->img.texture , NULL, &ballarr->arr[i]->img.rect);
    }
}

// return false if all the balls are out of the sdl window
bool CheckGameStatus( BallArr *ballarr ){
    int count = 0;
    int len = ballarr->len - 3;
    for( int i = 0; i < len; i++ ){
        if( ballarr->arr[i]->ingame == false ){
            count += 1;
        }
    }
    if( count == len ){
        return false;
    }
    return true;
}

// count balls that are in the game
void CheckInGameBalls( Frame *frame, BallArr *ballarr ){
    int len = ballarr->len - 3;
    for( int i = 0; i < len; i++ ){
       cpVect pos = cpBodyGetPosition(ballarr->arr[i]->body);
       if( -pos.y > frame->height ){
           ballarr->arr[i]->ingame = false;
       }
   }
}

void DestroyBallArr( cpSpace *space, BallArr *ballarr){
    for( int i = ballarr->len - 1; i >= 0; i-- ){
       DeleteBall( space, ballarr->arr[i] ); 
    }
    free(ballarr->arr);
    free(ballarr);
}
