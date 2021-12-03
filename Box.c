#include "Box.h"

Box* InitBox(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height, const char *path ){
    Box *box = (Box*)malloc( sizeof(Box) );
    box->body = cpBodyNewStatic();
    pos.x += width / 2.0;
    pos.y -= height / 2.0;
    cpBodySetPosition(box->body, pos);
    cpBodySetVelocity(box->body, cpvzero);
    box->shape = cpSpaceAddShape(space, cpBoxShapeNew(box->body, width, height, 0.01) );
    sscanf(path, "%s", box->img.sprite);
    SDL_Texture *texture = IMG_LoadTexture(renderer, box->img.sprite);
    box->img.texture = texture;
    box->img.rect.x = cpBodyGetPosition(box->body).x; 
    box->img.rect.y = - cpBodyGetPosition(box->body).y; 
    box->img.rect.w = width;
    box->img.rect.h = height;
    return box;
}

void PrintBox( SDL_Renderer *renderer, Box *box ){
    cpVect pos = cpBodyGetPosition(box->body);
    box->img.rect.x = pos.x - box->img.rect.w / 2.0;
    box->img.rect.y = -pos.y - box->img.rect.h / 2.0;
    SDL_RenderCopy(renderer, box->img.texture , NULL, &box->img.rect);
}

void DeleteBox( Box *box ){
    cpShapeFree(box->shape);
    cpBodyFree(box->body);
    SDL_DestroyTexture(box->img.texture);
    free(box);
}
