#include "init.h"

SDL_Window *window;
SDL_Renderer *render;

void InitSDL(char *caption)
{
        if (SDL_Init(SDL_INIT_EVERYTHING))
                fprintf(stderr, "Unable to initialize SDL2: %s\n", SDL_GetError());

        window = SDL_CreateWindow(caption,
                        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                        SWIDTH, SHEIGHT,
                        SDL_WINDOW_OPENGL);

        render = SDL_CreateRenderer(window, -1,
                        SDL_RENDERER_PRESENTVSYNC |
                        SDL_RENDERER_ACCELERATED);

        SDL_SetRelativeMouseMode(true);
}