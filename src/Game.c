#include "Game.h"

Game* InitGame(){
    Game* game = (Game*)malloc( sizeof(Game) );

    // specify dimensions of the sdl window (beware, map's objects positions are set manually)
    Frame frame = {.width = 700, .height = 700 };
    game->frame = frame;

    cpVect gravity = cpv(0, -7);

    // chipmunk space
    cpSpace *space = cpSpaceNew();
    cpSpaceSetGravity(space, gravity);
    game->space = space;

    // sdl window
    SDL_Window* window = SDL_CreateWindow("PinBall", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, frame.width, frame.height, SDL_WINDOW_OPENGL);
    game->window = window;
    SDL_Renderer *renderer = SDL_CreateRenderer(window,-1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    game->renderer = renderer;

    return game;
}

void DeleteGame(Game *game){
    SDL_DestroyRenderer( game->renderer );
    SDL_DestroyWindow(game->window);
    cpSpaceFree(game->space);
    free(game);
}
