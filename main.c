// external libraries
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_audio.h>
#include <stdbool.h>
#include <time.h>
#include "Chipmunk/include/chipmunk/chipmunk.h"

// my includes
#include "Ball.h"
#include "Frame.h"
#include "BallArr.h"
#include "Map.h"
#include "Flipper.h"
#include "Box.h"
#include "Game.h"
#include "Slingshot.h"

// draws borders of SDL_Rect 
static void WrapPic(SDL_Rect rect, SDL_Renderer *renderer){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x + rect.w, rect.y);
    SDL_RenderDrawLine(renderer, rect.x, rect.y + rect.h, rect.x + rect.w, rect.y + rect.h);
    SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x, rect.y + rect.h);
    SDL_RenderDrawLine(renderer, rect.x + rect.w, rect.y, rect.x + rect.w, rect.y + rect.h);
}

// release allocated memory
static void CleanUp(BallArr *ballarr, Map *map, Game *game){
    DestroyBallArr( ballarr );
    DestroyMap(map);
    DeleteGame( game );
}

// gathers events from SDL_PollEvent buffer, executes actions based on event types
static void CheckEvents( SDL_Event event, bool *running, BallArr *ballarr, Map *map ){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                // upon closing sdl window, change running var which consequntly stops the game loop
                *running = false;
            }
            if( event.type == SDL_KEYDOWN ){
                switch( event.key.keysym.sym ){
                    // left arrow key pressed
                    case SDLK_LEFT:
                        map->flips.arr[0]->state = FlipperMovingUp;
                        break;
                    // right arrow key pressed
                    case SDLK_RIGHT:
                        map->flips.arr[1]->state = FlipperMovingUp;
                        break;
                    // down arrow key pressed
                    case SDLK_DOWN:
                        cpBodyApplyImpulseAtLocalPoint(ballarr->arr[0]->body, cpv(0, 2000), cpv(0,0) );
                        cpBodyApplyImpulseAtLocalPoint(ballarr->arr[1]->body, cpv(0, 2000), cpv(0,0) );
                        break;
                    default:
                        break;
                }
            }
        }

}

static void GameLoop( BallArr *ballarr, Map *map, Game *game){
    cpFloat time = 0;
    cpFloat timeStep = 1.0/60.0;
    bool running = true;
    SDL_Event event;
    while(running){
        time += timeStep;

        CheckEvents( event, &running, ballarr, map );

        // set background
        SDL_SetRenderDrawColor(game->renderer, 105, 105, 105, 255);
        SDL_RenderClear(game->renderer);

        // print my structures on sdl window
        PrintBallArr( game->renderer, ballarr );
        PrintMap( game->space, game->renderer, map );

        // update position of flippers
        FlipperMove( game->space, map->flips.arr[0] );
        FlipperMove( game->space, map->flips.arr[1] );

        cpSpaceStep(game->space, timeStep);

        SDL_RenderPresent(game->renderer);

        CheckInGameBalls( &game->frame, ballarr );

        // if all balls from ballarray are outside of the sdl window, stop the game
        if( CheckGameStatus( ballarr ) == false ){
            printf("\n\n\tYou lost!\n\n\n");
            running = false;
        }
    }

}

int main(){
    // Init SDL
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    Game *game = InitGame();
    // all static bodies
    Map* map = InitMap(game->space, game->frame, game->renderer); 
    // array of balls
    BallArr *ballarr = InitBallArr( game->space, game->renderer, 2);

    // game logic
    GameLoop( ballarr, map, game );

    // free all alocated memory
    CleanUp(ballarr, map, game);

    IMG_Quit();
    SDL_Quit();
    return 0;
}