//
// Created by Maciej on 01.06.2022.
//

#ifndef TOWER_DEFENCE_GAME_BUILDER_H
#define TOWER_DEFENCE_GAME_BUILDER_H
#include "Tower.h"

class Builder{
public:
    static Tower smallTower(SDL_Renderer* rend, Position position){
        Tower tower = Tower(rend, position.x(), position.y(), SMALL_TOWER_RANGE, "../images/tower.png", bullets::arrow);
        return tower;
    }
    static Tower bigTower(SDL_Renderer* rend, Position position){
        Tower tower = Tower(rend, position.x(), position.y(), BIG_TOWER_RANGE, "../images/tower2.png", bullets::ball);
        return tower;
    }
};

#endif //TOWER_DEFENCE_GAME_BUILDER_H
