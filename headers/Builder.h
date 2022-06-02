//
// Created by Maciej on 01.06.2022.
//

#ifndef TOWER_DEFENCE_GAME_BUILDER_H
#define TOWER_DEFENCE_GAME_BUILDER_H
#include "Tower.h"

class Builder{
public:
    static Tower smallTower(SDL_Renderer* rend, Position position);
    static Tower bigTower(SDL_Renderer* rend, Position position);
};

#endif //TOWER_DEFENCE_GAME_BUILDER_H
