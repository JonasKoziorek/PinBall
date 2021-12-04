#include "Flipper.h"
#include <SDL2/SDL_render.h>

Flipper* InitFlipper(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height, FlipperSide side){
    Flipper *flip = (Flipper*)malloc( sizeof(Flipper) );
    flip->body = cpBodyNewStatic();
    flip->angle = 0;
    cpBodySetCenterOfGravity( flip->body, cpv( side == FlipperSideLeft ? -width / 2.0 : width / 2.0, height / 2) );
    pos.x += width / 2.0;
    pos.y -= height / 2.0;
    cpBodySetPosition(flip->body, pos);
    cpBodySetVelocity(flip->body, cpvzero);

    flip->shape = cpSpaceAddShape(space, cpBoxShapeNew(flip->body, width, height, 0.01) );
    cpShapeSetElasticity(flip->shape, 1.2);
    cpShapeSetFriction(flip->shape, 0.4);
    flip->side = side;
    flip->state = FlipperNotMoving;

    flip->rect.x = cpBodyGetPosition(flip->body).x- width / 2.0;
    flip->rect.y = - cpBodyGetPosition(flip->body).y - height / 2.0; 
    flip->rect.w = width;
    flip->rect.h = height;
    return flip;
}


void PrintFlipper( cpSpace *space, SDL_Renderer *renderer, Flipper *flip, SDL_Texture *texture ){
    cpVect pos = cpBodyGetPosition(flip->body);
    cpFloat angle = flip->angle;
    flip->rect.x = pos.x - flip->rect.w / 2.0;
    flip->rect.y = -pos.y - flip->rect.h / 2.0; 
        SDL_RenderCopyEx(renderer, texture , NULL, &flip->rect, -angle * 180.0 / 3.1415, NULL, flip->side == FlipperSideLeft ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    cpSpaceReindexShapesForBody( space, flip->body );
}

void FlipperMove( cpSpace *space, Flipper *flip, cpFloat timestep ){
    cpFloat angle = flip->angle;
    float angular_vel = M_PI_4;
    if( flip->side == FlipperSideLeft ){
        if( flip->state == FlipperNotMoving ){
            return;
        }
        else{
            cpBodySetAngularVelocity(flip->body, 
                    FlipperMovingUp == flip->state? angular_vel : -angular_vel);
        }
        if( angle >= M_PI / 2 ){
            flip->state = FlipperMovingDown;
        }
        if( angle < 0 ){
            flip->state = FlipperNotMoving;
            cpBodySetAngularVelocity(flip->body, 0);
            flip->angle = 0.01;
        }
    }
    else{
        if( flip->state == FlipperNotMoving ){
            return;
        }
        else{
            cpBodySetAngularVelocity(flip->body, 
                    flip->state == FlipperMovingUp ? -angular_vel : angular_vel );
        }
        if( angle <= -M_PI / 2 ){
            flip->state = FlipperMovingDown;
        }
        if( angle > 0 ){
            flip->state = FlipperNotMoving;
            cpBodySetAngularVelocity(flip->body, 0);
            flip->angle = -0.01;
        }
    }
    cpBodySetAngle( flip->body, angle);
    cpSpaceReindexShapesForBody( space, flip->body );
    flip->angle += cpBodyGetAngularVelocity(flip->body) * timestep;
}

void DeleteFlipper( cpSpace *space, Flipper *flip){
    cpSpaceRemoveShape( space, flip->shape );
    cpSpaceRemoveBody( space, flip->body );
    cpShapeFree( flip->shape );
    cpBodyFree( flip->body );
    free(flip);
}
