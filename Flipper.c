#include "Flipper.h"
#include <SDL2/SDL_render.h>

Flipper* InitFlipper(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height, const char *path, FlipperSide side){
    Flipper *flip = (Flipper*)malloc( sizeof(Flipper) );
    flip->body = cpBodyNewStatic();
    if( side == FlipperSideLeft ){
        cpBodySetCenterOfGravity( flip->body, cpv( -width / 2.0, height / 2) );
    }else{
        cpBodySetCenterOfGravity( flip->body, cpv( width / 2.0, height / 2) );
    }
    pos.x += width / 2.0;
    pos.y -= height / 2.0;
    cpBodySetPosition(flip->body, pos);
    cpBodySetVelocity(flip->body, cpvzero);
    cpBodySetAngle(flip->body, 0);

    flip->shape = cpSpaceAddShape(space, cpBoxShapeNew(flip->body, width, height, 0.01) );
    cpShapeSetElasticity(flip->shape, 1.2);
    cpShapeSetFriction(flip->shape, 0.4);
    sscanf(path, "%s", flip->img.sprite);
    flip->side = side;
    flip->state = FlipperNotMoving;

    SDL_Texture *texture = IMG_LoadTexture(renderer, flip->img.sprite);
    flip->img.texture = texture;
    flip->img.rect.x = cpBodyGetPosition(flip->body).x- width / 2.0;
    flip->img.rect.y = - cpBodyGetPosition(flip->body).y - height / 2.0; 
    flip->img.rect.w = width;
    flip->img.rect.h = height;
    return flip;
}


void PrintFlipper( cpSpace *space, SDL_Renderer *renderer, Flipper *flip ){
    cpVect pos = cpBodyGetPosition(flip->body);
    cpFloat angle = cpBodyGetAngle(flip->body);
    flip->img.rect.x = pos.x - flip->img.rect.w / 2.0;
    flip->img.rect.y = -pos.y - flip->img.rect.h / 2.0; 
    if( flip->side == FlipperSideLeft ){
        SDL_RenderCopyEx(renderer, flip->img.texture , NULL, &flip->img.rect, -angle * 180.0 / 3.1415, NULL, SDL_FLIP_HORIZONTAL);

    }else{
        SDL_RenderCopyEx(renderer, flip->img.texture , NULL, &flip->img.rect, -angle * 180.0 / 3.1415, NULL, SDL_FLIP_NONE);
    }
    cpSpaceReindexShapesForBody( space, flip->body );
}

void FlipperMove( cpSpace *space, Flipper *flip ){
    const float pi = 3.1415;
    cpFloat angle = cpBodyGetAngle(flip->body);
    if( flip->side == FlipperSideLeft ){
        if( flip->state == FlipperNotMoving ){
            return;
        }
        else if( flip->state == FlipperMovingUp ){
            cpBodySetAngle(flip->body, angle + 0.01 );
        }else{
            cpBodySetAngle(flip->body, angle - 0.01 );
        }
        if( angle >= pi / 2 ){
            flip->state = FlipperMovingDown;
        }
        if( angle < 0 ){
            flip->state = FlipperNotMoving;
            cpBodySetAngle(flip->body, 0 );
        }
    }else{
        if( flip->state == FlipperNotMoving ){
            return;
        }
        else if( flip->state == FlipperMovingUp ){
            cpBodySetAngle(flip->body, angle-0.01 );
        }else{
            cpBodySetAngle(flip->body, angle+0.01 );
        }
        if( angle <= -pi / 2 ){
            flip->state = FlipperMovingDown;
        }
        if( angle > 0 ){
            flip->state = FlipperNotMoving;
            cpBodySetAngle(flip->body, 0 );
        }
    }
    cpSpaceReindexShapesForBody( space, flip->body );
}

void DeleteFlipper(Flipper *flip){
    cpShapeFree( flip->shape );
    cpBodyFree( flip->body );
    SDL_DestroyTexture( flip->img.texture );
    free(flip);
}
