//
// Created by Maciej on 02.06.2022.
//

#ifndef TOWER_DEFENCE_GAME_WAVEENGINE_H
#define TOWER_DEFENCE_GAME_WAVEENGINE_H
#include "SDL.h"
#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "math.h"
#include "Wave.h"
#include "Enemy.h"
#include "Common.h"
#include <string.h>
#include "Tower.h"
#include "Map.h"

class WaveEngine{
    char levelWaveName[100]="..";
    std::vector<Wave> waves;
    int currentWave = 0;
    std::vector<Enemy> enemyList;
    SDL_Renderer* rend;
    int noEnemies = 0;
    int timer = 0;
    Position startPosition;

public:
    WaveEngine(SDL_Renderer* rend, char* levelName, Position start)
    :rend(rend)
    ,startPosition(start){
        char a[100];
        strcpy(a, levelName);
        strcat(levelWaveName, strtok(a , "."));
        strcat(levelWaveName, "_wave.txt");
        loadLevel();
    }

    std::vector<std::string> splitBySpace(std::string line);

    void loadLevel();

    void getWave();

    void addEnemy(Position position);;

    Directions findNextStep(Enemy enemy, Map map);;

    enum gameStatus waveStep(Map map);;

    void enemyStep(Position towerPosition, Tower tower);

    void addEnemyFromWave();;

    bool getEndStatus(){
        return currentWave >= waves.size() && noEnemies == 0 && enemyList.size() == 0;
    }
};

#endif //TOWER_DEFENCE_GAME_WAVEENGINE_H
