#include "Frame.h"

void DrawFrame( Frame *frame, SDL_Renderer *renderer ){
        SDL_RenderDrawLine(renderer, 10, 10, 10, frame->height - 10);
        SDL_RenderDrawLine(renderer, 10, 10, frame->width - 10, 10);
        SDL_RenderDrawLine(renderer, 10, frame->height - 10, frame->width - 10, frame->height - 10);
        SDL_RenderDrawLine(renderer, frame->width - 10, 10, frame->width - 10, frame->height - 10);
}
