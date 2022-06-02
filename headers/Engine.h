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
#include "GameBar.h"
#include "Builder.h"
#include <thread>

class Engine{
private:
    bool isRunning;
    SDL_Renderer* rend;
    std::vector<Enemy> enemyList;
    std::vector<Tower> towerList;

    int NumberOfEnemies, NumberOfTowers;
    Map map;
    GameBar gameBar;

    int noEnemies = 0;

public:
    Engine(SDL_Renderer* rend)
    :isRunning(false)
    ,rend(rend)
    ,NumberOfEnemies(0)
    ,NumberOfTowers(0)
    ,map(Map(rend))
    ,gameBar(rend){

    }

    void start();

    void addEnemy(Position position);

    void addTower(Position position, enum towers type);

    void engineStep();

    Directions findNextStep(Enemy enemy);

    void waveStep();

    void generateWave();

    void addEnemyFromWave();
};

#endif //TOWER_DEFENCE_GAME_ENGINE_H
