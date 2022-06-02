//
// Created by Maciej on 02.06.2022.
//

#ifndef TOWER_DEFENCE_GAME_SDL_CIRCLE_H
#define TOWER_DEFENCE_GAME_SDL_CIRCLE_H
#include "SDL.h"

class SDL_Circle{
public:
    static int Draw(SDL_Renderer * renderer, int x, int y, int radius);

};
#endif //TOWER_DEFENCE_GAME_SDL_CIRCLE_H
