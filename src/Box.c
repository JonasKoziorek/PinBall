#include "Box.h"

Box* InitBox(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height){
    Box *box = (Box*)malloc( sizeof(Box) );
    box->body = cpBodyNewStatic();
    pos.x += width / 2.0;
    pos.y -= height / 2.0;
    cpBodySetPosition(box->body, pos);
    cpBodySetVelocity(box->body, cpvzero);
    box->shape = cpSpaceAddShape(space, cpBoxShapeNew(box->body, width, height, 0.01) );
    box->rect.x = cpBodyGetPosition(box->body).x; 
    box->rect.y = - cpBodyGetPosition(box->body).y; 
    box->rect.w = width;
    box->rect.h = height;
    return box;
}

void PrintBox( SDL_Renderer *renderer, Box *box, SDL_Texture *texture ){
    cpVect pos = cpBodyGetPosition(box->body);
    box->rect.x = pos.x - box->rect.w / 2.0;
    box->rect.y = -pos.y - box->rect.h / 2.0;
    SDL_RenderCopy(renderer, texture , NULL, &box->rect);
}

void DeleteBox( cpSpace *space, Box *box ){
    cpSpaceRemoveShape( space, box->shape );
    cpShapeFree(box->shape);
    cpBodyFree(box->body);
    free(box);
}
