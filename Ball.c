#include "Ball.h"

Ball* InitBall(cpSpace *space, SDL_Renderer *renderer, cpVect pos, cpVect vel, float radius, const char *path){
    Ball *ball = (Ball*)malloc( sizeof(Ball) );
    float mass = 10;
    cpFloat moment = cpMomentForCircle(mass, 0, radius, cpvzero);
    ball->body = cpSpaceAddBody(space, cpBodyNew(mass, moment)); 
    cpBodySetPosition(ball->body, pos);
    cpBodySetVelocity(ball->body, vel);
    ball->shape = cpSpaceAddShape(space, cpCircleShapeNew(ball->body, radius, cpvzero));
    cpShapeSetElasticity(ball->shape, 1.0);
    cpShapeSetFriction(ball->shape, 0.7);

    sscanf(path, "%s", ball->img.sprite);
    
    SDL_Texture *texture = IMG_LoadTexture(renderer, ball->img.sprite);
    ball->img.texture = texture;
    ball->img.rect.x = cpBodyGetPosition(ball->body).x; 
    ball->img.rect.y = - cpBodyGetPosition(ball->body).y; 
    ball->img.rect.w = radius * 2;
    ball->img.rect.h = radius * 2;

    ball->ingame = true;
    return ball;
}

// bumpers are the same as balls, but they are static
Ball* InitBumper(cpSpace *space, SDL_Renderer *renderer, cpVect pos, cpVect vel, float radius, const char *path){
    Ball *ball = (Ball*)malloc( sizeof(Ball) );
    ball->body = cpBodyNewStatic(); 
    cpBodySetPosition(ball->body, pos);
    cpBodySetVelocity(ball->body, vel);
    ball->shape = cpSpaceAddShape(space, cpCircleShapeNew(ball->body, radius, cpvzero));
    cpShapeSetElasticity(ball->shape, 1.0);
    cpShapeSetFriction(ball->shape, 0.7);

    sscanf(path, "%s", ball->img.sprite);
    
    SDL_Texture *texture = IMG_LoadTexture(renderer, ball->img.sprite);
    ball->img.texture = texture;
    ball->img.rect.x = cpBodyGetPosition(ball->body).x; 
    ball->img.rect.y = - cpBodyGetPosition(ball->body).y; 
    ball->img.rect.w = radius * 2;
    ball->img.rect.h = radius * 2;

    ball->ingame = true;

    return ball;
}

void PrintBall( SDL_Renderer *renderer, Ball *ball ){
    cpVect pos = cpBodyGetPosition(ball->body);
    ball->img.rect.x = pos.x - cpCircleShapeGetRadius(ball->shape);
    ball->img.rect.y = -pos.y - cpCircleShapeGetRadius(ball->shape);
    SDL_RenderCopy(renderer, ball->img.texture , NULL, &ball->img.rect);
}

void DeleteBall( Ball *ball ){
    cpBodyFree(ball->body);
    cpShapeFree(ball->shape);
    SDL_DestroyTexture(ball->img.texture);
    free(ball);
}

