//
// Created by Maciej on 17.05.2022.
//

#ifndef TOWER_DEFENCE_GAME_ENGINE_H
#define TOWER_DEFENCE_GAME_ENGINE_H
#include <iostream>
#include <SDL.h>
#include <SDL_timer.h>
#include <vector>
#include "../headers/Common.h"
#include "Position.h"
#include "Enemy.h"
#include "Tower.h"
#include "Map.h"
#include "Bullet.h"
#include "LevelEngine.h"
#include "MenuScreen.h"
#include "Builder.h"


class Engine{
private:
    bool isRunning;
    SDL_Renderer* rend;
    LevelEngine *levelEngine = (LevelEngine*) calloc(sizeof (LevelEngine), 10);

public:
    Engine(SDL_Renderer* rend)
    :isRunning(false)
    ,rend(rend){
    }

    void start();

};

#endif //TOWER_DEFENCE_GAME_ENGINE_H
