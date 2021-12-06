#include "Spring.h"

Spring* InitSpring(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height){
    Spring *spring = (Spring*)malloc( sizeof(Spring) );
    spring->body = cpSpaceAddBody(space, cpBodyNew(10,10));
    pos.x += width / 2.0;
    pos.y -= height / 2.0;
    cpBodySetPosition(spring->body, pos);
    cpBodySetVelocity(spring->body, cpvzero);
    spring->shape = cpSpaceAddShape(space, cpBoxShapeNew(spring->body, width, height, 0.01) );
    spring->rect.x = cpBodyGetPosition(spring->body).x; 
    spring->rect.y = - cpBodyGetPosition(spring->body).y; 
    spring->rect.w = width;
    spring->rect.h = height;
    return spring;
}

void PrintSpring( SDL_Renderer *renderer, Spring *spring, SDL_Texture *texture ){
    cpVect pos = cpBodyGetPosition(spring->body);
    spring->rect.x = pos.x - spring->rect.w / 2.0;
    spring->rect.y = -pos.y - spring->rect.h / 2.0;
    SDL_RenderCopy(renderer, texture , NULL, &spring->rect);
}

void DeleteSpring( cpSpace *space, Spring *spring ){
    cpSpaceRemoveBody( space, spring->body );
    cpSpaceRemoveShape( space, spring->shape );
    cpShapeFree(spring->shape);
    cpBodyFree(spring->body);
    free(spring);
}

void SpringMove( Spring *spring ){
    cpVect pos = cpBodyGetPosition(spring->body);
    if( spring->state == SpringMovingUp ){
        cpBodySetVelocity( spring->body, cpv( 0, 100 ) );
    }
    if( spring->state == SpringMovingDown ){
        cpBodySetVelocity( spring->body, cpv( 0, -10 ) );
    }
    if( pos.y > -450 ){
        spring->state = SpringMovingDown;
    }
    if( pos.y < -500 ){
        spring->state = SpringIdle;
    }
}
