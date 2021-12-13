#include "Slingshot.h"
#include <SDL2/SDL_render.h>

// I have already chosen image for the Slingshot object and this function just computes approximate vertices of this object
void ComputeSlingVerts(float width, float height, cpVect *verts, SlingSide type){
   if( type == SlingSideLeft ){
        verts[0] = cpv( -width / 2.0, height / 2.0 );
        verts[1] = cpv( width / 2.0, -height / 2.0 );
        verts[2] = cpv( -width / 2.0, -height / 4.0 );
        verts[3] = cpv( -width / 2.0, height / 2.0 );
   }
   else{
        verts[0] = cpv( width / 2.0, height / 2.0 );
        verts[1] = cpv( -width / 2.0, -height / 2.0 );
        verts[2] = cpv( width / 2.0, -height / 4.0 );
        verts[3] = cpv( width / 2.0, height / 2.0 );
   }
}

Slingshot* InitSlingshot(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height, SlingSide type ){
    Slingshot *sling = (Slingshot*)malloc( sizeof(Slingshot) );
    sling->body = cpBodyNewStatic();
    sling->type = type;

    // this is needed to match sdl view of rect and cpBodyPos
    pos.x += width / 2.0;
    pos.y -= height / 2.0;

    cpBodySetPosition(sling->body, pos);
    cpBodySetVelocity(sling->body, cpvzero);

    int len = 4;
    float radius = 10;
    cpVect verts[len]; 
    ComputeSlingVerts(width, height, verts, sling->type);
    sling->shape = cpSpaceAddShape(space, cpPolyShapeNewRaw(sling->body, len, verts, radius) );
    cpShapeSetElasticity(sling->shape, 0.2);
    cpShapeSetFriction(sling->shape, 2.0);

    // setup sdl texture and rect
    sling->rect.x = cpBodyGetPosition(sling->body).x - width / 2.0; 
    sling->rect.y = - cpBodyGetPosition(sling->body).y - height / 2.0; 
    sling->rect.w = width;
    sling->rect.h = height;

    return sling;
}

// display slingshot image on sdl window
// flip image according to the slingshot type
void PrintSlingshot( SDL_Renderer *renderer, Slingshot *sling, SDL_Texture *texture){
    cpVect pos = cpBodyGetPosition(sling->body);
    sling->rect.x = pos.x - sling->rect.w / 2.0;
    sling->rect.y = -pos.y - sling->rect.h / 2.0;
    SDL_RenderCopyEx(renderer, texture , NULL, &sling->rect, 0, NULL, sling->type == SlingSideRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL);

}

// free memory allocated in InitSlingshot
void DeleteSlingshot( cpSpace *space, Slingshot *sling ){
    cpSpaceRemoveShape( space, sling->shape );
    cpShapeFree(sling->shape);
    cpBodyFree(sling->body);
    free(sling);
}
