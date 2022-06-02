//
// Created by Maciej on 02.06.2022.
//

#ifndef TOWER_DEFENCE_GAME_LEVELENGINE_H
#define TOWER_DEFENCE_GAME_LEVELENGINE_H
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
#include "Builder.h"
#include "GameBar.h"
#include "WaveEngine.h"
#include "CoinLabel.h"
#include <SDL2/SDL_ttf.h>


class LevelEngine{
private:

    std::vector<Tower> towerList;
    std::vector<MapObject> objects;
    Map map;
    int noEnemies = 0;
    bool isRunning = true;
    SDL_Renderer* rend;
    enum gameStatus gameStatus_ = gameStatus::waiting;
    GameBar gameBar;
    WaveEngine waveEngine;

public:
    LevelEngine(SDL_Renderer* rend, char* levelName)
    :map(Map(rend, levelName))
    ,rend(rend)
    ,gameBar(GameBar(rend))
    ,waveEngine(WaveEngine(rend, levelName, map.getStart()))
    {
    }

    void start();


    void addTower(Position position, enum towers type);;

    void engineStep();

    void generateWave();

    enum gameStatus getStatus(){
        return gameStatus_;
    }

    void defeatScreen();

    void victoryScreen();

    void click(SDL_Event event);

    void clickLeftBar(SDL_Event event, Position position);
};

#endif //TOWER_DEFENCE_GAME_LEVELENGINE_H
