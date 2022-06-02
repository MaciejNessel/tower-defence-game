//
// Created by Maciej on 02.06.2022.
//
#include "../headers/Builder.h"

Tower Builder::smallTower(SDL_Renderer *rend, Position position) {
    Tower tower = Tower(rend, position.x(), position.y(), SMALL_TOWER_RANGE, "../images/tower.png", bullets::arrow);
    return tower;
}

Tower Builder::bigTower(SDL_Renderer *rend, Position position) {
    Tower tower = Tower(rend, position.x(), position.y(), BIG_TOWER_RANGE, "../images/tower2.png", bullets::ball);
    return tower;
}
