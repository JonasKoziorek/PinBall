#pragma once
#include "SDL2/SDL_image.h"

typedef struct{
    // path to the image
    char sprite[50];
    SDL_Rect rect;
    SDL_Texture *texture;
}Img;
