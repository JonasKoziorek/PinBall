#include "Slingshot.h"

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

Slingshot* InitSlingshot(cpSpace *space, SDL_Renderer *renderer, cpVect pos, float width, float height, SlingSide type, const char *path ){
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
    cpVect *verts = (cpVect*)malloc( len * sizeof(cpVect) );
    ComputeSlingVerts(width, height, verts, sling->type);
    sling->shape = cpSpaceAddShape(space, cpPolyShapeNewRaw(sling->body, len, verts, radius) );
    cpShapeSetFriction(sling->shape, 5.0);
    cpShapeSetElasticity(sling->shape, 0.2);

    free(verts);

    // setup sdl texture and rect
    sscanf(path, "%s", sling->img.sprite);
    SDL_Texture *texture = IMG_LoadTexture(renderer, sling->img.sprite);
    sling->img.texture = texture;
    sling->img.rect.x = cpBodyGetPosition(sling->body).x; 
    sling->img.rect.y = - cpBodyGetPosition(sling->body).y; 
    sling->img.rect.w = width;
    sling->img.rect.h = height;

    return sling;
}

// display slingshot image on sdl window
// flip image according to the slingshot type
void PrintSlingshot( SDL_Renderer *renderer, Slingshot *sling ){
    cpVect pos = cpBodyGetPosition(sling->body);
    sling->img.rect.x = pos.x - sling->img.rect.w / 2.0;
    sling->img.rect.y = -pos.y - sling->img.rect.h / 2.0;
    
    if( sling->type == SlingSideRight ){
        SDL_RenderCopyEx(renderer, sling->img.texture , NULL, &sling->img.rect, 0, NULL, SDL_FLIP_NONE);

    }
    else{
        SDL_RenderCopyEx(renderer, sling->img.texture , NULL, &sling->img.rect, 0, NULL, SDL_FLIP_HORIZONTAL);

    }
}

// free memory allocated in InitSlingshot
void DeleteSlingshot( Slingshot *sling ){
    cpShapeFree(sling->shape);
    cpBodyFree(sling->body);
    SDL_DestroyTexture(sling->img.texture);
    free(sling);
}
