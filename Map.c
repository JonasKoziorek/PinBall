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

void SetupBoxes( cpSpace *space, Map *map, const int len, SDL_Renderer *renderer){
    Box **arr = (Box**)malloc( len * sizeof(Box*) );
    map->boxes.arr = arr;
    map->boxes.len = len;

    // lower left padding
    map->boxes.arr[0] = InitBox( space, renderer, cpv(0, -650), 200, 50, "images/wall.jpg");
    MapSetObjectFriEla( map->boxes.arr[0]->shape, map->fri, map->ela );

    // lower right padding
    map->boxes.arr[1] = InitBox( space, renderer, cpv(500, -650), 200, 50, "images/wall.jpg");
    MapSetObjectFriEla( map->boxes.arr[1]->shape, map->fri, map->ela );

    // left bounce wall
    map->boxes.arr[2] = InitBox( space, renderer, cpv(35, -250), 2, 400, "images/wall.jpg");
    MapSetObjectFriEla( map->boxes.arr[2]->shape, map->fri, map->ela );

    // right bounce wall
    map->boxes.arr[3] = InitBox( space, renderer, cpv(665, -250), 2, 400, "images/wall.jpg");
    MapSetObjectFriEla( map->boxes.arr[3]->shape, map->fri, map->ela );

    // bottom left bounce wall
    map->boxes.arr[4] = InitBox( space, renderer, cpv(0, -500), 35, 150, "images/wall.jpg");
    MapSetObjectFriEla( map->boxes.arr[4]->shape, map->fri, map->ela );

    // bottom right bounce wall
    map->boxes.arr[5] = InitBox( space, renderer, cpv(665, -500), 35, 150, "images/wall.jpg");
    MapSetObjectFriEla( map->boxes.arr[5]->shape, map->fri, map->ela );

}

void SetupFlippers( cpSpace *space, SDL_Renderer *renderer , Map *map){
    map->flips.arr[0] = InitFlipper(space, renderer, cpv(200,-650), 120, 30, "images/flipper.png", FlipperSideLeft);
     map->flips.arr[1] = InitFlipper(space, renderer, cpv(380,-650), 120, 30, "images/flipper.png", FlipperSideRight);
}

void SetupCurves( cpSpace *space, Map *map, const int len, SDL_Renderer *renderer){
   Curve **arr = (Curve**)malloc( len * sizeof(Curve*) ); 
   map->curves.arr = arr;
   map->curves.len = len;

   // lower right
   map->curves.arr[0] = InitCurve( space, renderer, cpv( 500, -500 ), 165, 150, CurveRotSE, "images/rcurve.png");
    MapSetObjectFriEla( map->curves.arr[0]->shape, map->fri, map->ela );

    // lower left
   map->curves.arr[1] = InitCurve( space, renderer, cpv( 35, -500 ), 165, 150, CurveRotSW, "images/rcurve.png");
    MapSetObjectFriEla( map->curves.arr[1]->shape, map->fri, map->ela );

    // upper right
   map->curves.arr[2] = InitCurve( space, renderer, cpv( 350, 0 ), 352,150, CurveRotNE, "images/rcurve.png");
    MapSetObjectFriEla( map->curves.arr[2]->shape, map->fri, map->ela );

    // upper left
   map->curves.arr[3] = InitCurve( space, renderer, cpv( -2, 0 ), 350, 150, CurveRotNW, "images/rcurve.png");
    MapSetObjectFriEla( map->curves.arr[3]->shape, map->fri, map->ela );
}

void SetupSlingshots( Map *map, cpSpace *space, SDL_Renderer *renderer, int len){
    Slingshot **arr = (Slingshot**)malloc( len * sizeof( Slingshot*) );
    map->slings.arr = arr;
    map->slings.len = len;

    map->slings.arr[0] = InitSlingshot( space, renderer, cpv(150, -380), 150, 150, SlingSideLeft, "images/slingshot.png");
    map->slings.arr[1] = InitSlingshot( space, renderer, cpv(450, -380), 150, 150, SlingSideRight, "images/slingshot.png");
    
}

// prints all the objects in map struct
void PrintMap( cpSpace *space, SDL_Renderer *renderer, Map *map ){
        for( int i = 0; i < map->boxes.len; i++ ){
            PrintBox( renderer, map->boxes.arr[i] );
        }
        for( int i = 0; i < 2; i++ ){
            PrintFlipper( space, renderer, map->flips.arr[i] );
        }
        for( int i = 0; i < map->curves.len; i++ ){
            PrintCurve( renderer, map->curves.arr[i] );
        }
        for( int i = 0; i < map->slings.len; i++ ){
            PrintSlingshot( renderer, map->slings.arr[i] );
        }
}


Map* InitMap( cpSpace *space, Frame frame, SDL_Renderer *renderer ){

    // lengths are set manually, because map is set manually as well

    Map* map = (Map*)malloc( sizeof(Map) );

    map->fri = 1.0;
    map->ela = 0.1;

    // curves
    const int curvelen = 4;
    SetupCurves( space, map, curvelen, renderer );

    // walls
    const int wallen = 5;
    SetupWalls( space, map, wallen, frame ); 

    // boxes
    const int boxlen = 6;
    SetupBoxes( space, map, boxlen, renderer );

    // flippers
    SetupFlippers( space, renderer, map );  

    // slingshots
    const int slinglen = 2;
    SetupSlingshots( map, space, renderer, slinglen );

    return map;
}

    
void DestroyMap( Map *map ){
    // most of the objects are stored in an array of pointers, both allocated. That's why I iterate through the array and free individual structs, then free the array itself.

    for( int i = map->walls.len - 1; i >= 0; i-- ){
       cpShapeFree(map->walls.arr[i]);
    }
    free(map->walls.arr);

    for( int j = map->boxes.len - 1; j >= 0; j-- ){
        DeleteBox( map->boxes.arr[j] );  
    }
    free(map->boxes.arr);

    for( int i = 0; i < 2; i++ ){
        DeleteFlipper( map->flips.arr[i] );
    }

    for( int i = 0; i < map->curves.len; i++ ){
        DeleteCurve( map->curves.arr[i] );
    }
    free( map->curves.arr );
    
    for( int i = 0; i < map->slings.len; i++ ){
        DeleteSlingshot( map->slings.arr[i] );
    }
    free( map->slings.arr );

    free(map);
}