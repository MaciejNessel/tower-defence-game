#include <SDL.h>
#include <SDL_timer.h>
#include "../headers/Engine.h"
#include "../headers/Common.h"

int main(int argc, char *argv[])
{
    SDL_Window* win = SDL_CreateWindow("Tower defence",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       WINDOW_WIDTH, WINDOW_HEIGHT, 0);

    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);

    Engine engine = Engine(rend);
    engine.start();

    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();

    return 0;
}