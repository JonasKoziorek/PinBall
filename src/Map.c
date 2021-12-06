#include "Map.h"
#include <SDL2/SDL_render.h>

// sets friction and elasticity to cpShape
void MapSetObjectFriEla( cpShape *shape, cpFloat fri, cpFloat ela ){
    cpShapeSetFriction(shape, fri);
    cpShapeSetElasticity(shape, ela);
}

void SetupWall(Map *map, cpSpace *space,int i, cpVect p1, cpVect p2 ){
    map->walls.arr[i] = cpSegmentShapeNew(cpSpaceGetStaticBody(space), p1, p2, 0);
    MapSetObjectFriEla( map->walls.arr[i], map->fri, map->ela );
    cpSpaceAddShape(space, map->walls.arr[i]);
}

// invisible borders of the sdl window
void SetupWalls( cpSpace *space, Map *map, const int len, Frame frame ){
    cpShape **arr = (cpShape**)malloc( len * sizeof(cpShape*) );
    map->walls.arr = arr;
    map->walls.len = len;

    // upper boundary
    SetupWall( map, space, 0, cpv(0, 0), cpv(frame.width, 0) );

    // left boundary
    SetupWall( map, space, 1, cpv(0, 0), cpv(0, -frame.height) );

    // lower left boundary
    SetupWall( map, space, 2, cpv(0, -frame.height), cpv(200, -frame.height) );

    // lower right boundary
    SetupWall( map, space, 3, cpv(500, -frame.height), cpv(frame.width, -frame.height) );

    // right boundary
    SetupWall( map, space, 4, cpv(frame.width, 0), cpv(frame.width, -frame.height) );

}

void SetupBoxes( cpSpace *space, Map *map, const int len, SDL_Renderer *renderer, const char *path){
    Box **arr = (Box**)malloc( len * sizeof(Box*) );
    map->boxes.arr = arr;
    map->boxes.len = len;
    map->boxes.texture = IMG_LoadTexture(renderer, path);

    // lower left padding
    map->boxes.arr[0] = InitBox( space, renderer, cpv(0, -650), 200, 50);
    MapSetObjectFriEla( map->boxes.arr[0]->shape, map->fri, map->ela );

    // lower right padding
    map->boxes.arr[1] = InitBox( space, renderer, cpv(500, -650), 200, 50);
    MapSetObjectFriEla( map->boxes.arr[1]->shape, map->fri, map->ela );

    // left bounce wall
    map->boxes.arr[2] = InitBox( space, renderer, cpv(35, -250), 2, 400);
    MapSetObjectFriEla( map->boxes.arr[2]->shape, map->fri, map->ela );

    // right bounce wall
    map->boxes.arr[3] = InitBox( space, renderer, cpv(665, -250), 2, 400);
    MapSetObjectFriEla( map->boxes.arr[3]->shape, map->fri, map->ela );

    // bottom left bounce wall
    map->boxes.arr[4] = InitBox( space, renderer, cpv(0, -500), 35, 150);
    MapSetObjectFriEla( map->boxes.arr[4]->shape, map->fri, map->ela );

    // bottom right bounce wall
    map->boxes.arr[5] = InitBox( space, renderer, cpv(665, -500), 35, 150);
    MapSetObjectFriEla( map->boxes.arr[5]->shape, map->fri, map->ela );

}

void SetupSprings( cpSpace *space, Map *map, const int len, SDL_Renderer *renderer, const char *path){
    Spring **arr = (Spring**)malloc( len * sizeof(Spring*) );
    map->springs.arr = arr;
    map->springs.len = len;
    map->springs.texture = IMG_LoadTexture(renderer, path);

    // left
    map->springs.arr[0] = InitSpring( space, renderer, cpv(0, -450), 35, 10);
    map->springs.arr[0]->state = SpringIdle;
    MapSetObjectFriEla( map->springs.arr[0]->shape, map->fri, map->ela );

    // right
    map->springs.arr[1] = InitSpring( space, renderer, cpv(665, -450), 35, 10);
    map->springs.arr[1]->state = SpringIdle;
    MapSetObjectFriEla( map->springs.arr[0]->shape, map->fri, map->ela );
    MapSetObjectFriEla( map->springs.arr[1]->shape, map->fri, map->ela );
}

void SetupFlippers( cpSpace *space, SDL_Renderer *renderer , Map *map, const char *path){
    map->flips.texture =  IMG_LoadTexture(renderer, path);
    map->flips.arr[0] = InitFlipper(space, renderer, cpv(200,-650), 130, 30, FlipperSideLeft);
     map->flips.arr[1] = InitFlipper(space, renderer, cpv(370,-650), 130, 30, FlipperSideRight);
}

void SetupCurves( cpSpace *space, Map *map, const int len, SDL_Renderer *renderer, const char *path){
   Curve **arr = (Curve**)malloc( len * sizeof(Curve*) ); 
   map->curves.arr = arr;
   map->curves.len = len;
   map->curves.texture =  IMG_LoadTexture(renderer, path);

   // lower right
   map->curves.arr[0] = InitCurve( space, renderer, cpv( 500, -500 ), 165, 150, CurveRotSE );
    MapSetObjectFriEla( map->curves.arr[0]->shape, map->fri, map->ela );

    // lower left
   map->curves.arr[1] = InitCurve( space, renderer, cpv( 35, -500 ), 165, 150, CurveRotSW );
    MapSetObjectFriEla( map->curves.arr[1]->shape, map->fri, map->ela );

    // upper right
   map->curves.arr[2] = InitCurve( space, renderer, cpv( 350, 0 ), 352,150, CurveRotNE );
    MapSetObjectFriEla( map->curves.arr[2]->shape, map->fri, map->ela );

    // upper left
   map->curves.arr[3] = InitCurve( space, renderer, cpv( -2, 0 ), 350, 150, CurveRotNW );
    MapSetObjectFriEla( map->curves.arr[3]->shape, map->fri, map->ela );
}

void SetupSlingshots( Map *map, cpSpace *space, SDL_Renderer *renderer, int len, const char* path){
    Slingshot **arr = (Slingshot**)malloc( len * sizeof( Slingshot*) );
    map->slings.arr = arr;
    map->slings.len = len;
    map->slings.texture =  IMG_LoadTexture(renderer, path);

    map->slings.arr[0] = InitSlingshot( space, renderer, cpv(120, -380), 150, 150, SlingSideLeft );
    map->slings.arr[1] = InitSlingshot( space, renderer, cpv(460, -380), 150, 150, SlingSideRight );
    
}

// prints all the objects in map struct
void PrintMap( cpSpace *space, SDL_Renderer *renderer, Map *map ){
        for( int i = 0; i < map->boxes.len; i++ ){
            PrintBox( renderer, map->boxes.arr[i], map->boxes.texture );
        }
        for( int i = 0; i < 2; i++ ){
            PrintFlipper( space, renderer, map->flips.arr[i], map->flips.texture );
        }
        for( int i = 0; i < map->curves.len; i++ ){
            PrintCurve( renderer, map->curves.arr[i], map->curves.texture );
        }
        for( int i = 0; i < map->slings.len; i++ ){
            PrintSlingshot( renderer, map->slings.arr[i], map->slings.texture );
        }
        for( int i = 0; i < map->springs.len; i++ ){
            PrintSpring( renderer, map->springs.arr[i], map->springs.texture );
        }
}


Map* InitMap( cpSpace *space, Frame frame, SDL_Renderer *renderer ){

    // lengths are set manually, because map is set manually as well

    Map* map = (Map*)malloc( sizeof(Map) );

    map->fri = 0.5;
    map->ela = 0.3;

    // curves
    const int curvelen = 4;
    SetupCurves( space, map, curvelen, renderer, "images/rcurve.png" );

    // walls
    const int wallen = 5;
    SetupWalls( space, map, wallen, frame ); 

    // boxes
    const int boxlen = 6;
    SetupBoxes( space, map, boxlen, renderer, "images/wall.jpg" );

    // flippers
    SetupFlippers( space, renderer, map, "images/flipper.png" );  

    // slingshots
    const int slinglen = 2;
    SetupSlingshots( map, space, renderer, slinglen, "images/slingshot.png" );

    // springs
    SetupSprings( space, map, 2, renderer, "images/black.png" );

    return map;
}

    
void DestroyMap( cpSpace *space, Map *map ){
    // most of the objects are stored in an array of pointers, both allocated. That's why I iterate through the array and free individual structs, then free the array itself.

    for( int i = map->walls.len - 1; i >= 0; i-- ){
       cpSpaceRemoveShape( space, map->walls.arr[i] );
       cpShapeFree(map->walls.arr[i]);
    }
    free(map->walls.arr);

    for( int j = map->boxes.len - 1; j >= 0; j-- ){
        DeleteBox( space, map->boxes.arr[j] );  
    }
    SDL_DestroyTexture(map->boxes.texture);
    free(map->boxes.arr);

    for( int j = map->springs.len - 1; j >= 0; j-- ){
        DeleteSpring( space, map->springs.arr[j] );  
    }
    SDL_DestroyTexture(map->springs.texture);
    free(map->springs.arr);

    for( int i = 0; i < 2; i++ ){
        DeleteFlipper( space, map->flips.arr[i] );
    }
    SDL_DestroyTexture(map->flips.texture);

    for( int i = 0; i < map->curves.len; i++ ){
        DeleteCurve( space, map->curves.arr[i] );
    }
    SDL_DestroyTexture(map->curves.texture);
    free( map->curves.arr );
    
    for( int i = 0; i < map->slings.len; i++ ){
        DeleteSlingshot( space, map->slings.arr[i] );
    }
    SDL_DestroyTexture(map->slings.texture);
    free( map->slings.arr );

    free(map);
}
