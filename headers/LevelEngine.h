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
    CoinLabel coinLabel;
    int coins = 100;
    bool isEnd = false;

public:
    LevelEngine(SDL_Renderer* rend, char* levelName)
    :map(Map(rend, levelName))
    ,rend(rend)
    ,gameBar(GameBar(rend))
    ,waveEngine(WaveEngine(rend, levelName, map.getStart()))
    ,coinLabel(CoinLabel(0, 0, 0, rend))
    {
    }

    ~LevelEngine(){
        for(int i=0; i<towerList.size(); i++){
            towerList.at(i).destroy();
        }
        for(int i=0; i<objects.size(); i++){
            objects.at(i).destroy();
        }
        map.destroy();
        gameBar.destroy();
        coinLabel.destroy();
        waveEngine.destroy();
    }

    void start();

    void addTower(Position position, enum towers type);

    void engineStep();

    void generateWave();

    enum gameStatus getStatus(){
        return gameStatus_;
    }

    void defeatScreen();

    void victoryScreen();

    void click(SDL_Event event);

    void clickLeftBar(SDL_Event event, Position position);

    bool isOccupied(Position position);
};

#endif //TOWER_DEFENCE_GAME_LEVELENGINE_H
