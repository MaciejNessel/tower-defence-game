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

class LevelEngine{
private:

    std::vector<Tower> towerList;
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
    {}

    void start(){
        int timer = 0;
        SDL_Event event;
        GameBarObject *result = nullptr;

        while (isRunning){
            if(waveEngine.getEndStatus()){
                isRunning = false;
                break;
            }
            timer ++;
            SDL_Event event;
            GameBarObject *result = nullptr;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT: isRunning = false; break;
                    case SDL_MOUSEBUTTONDOWN: result = gameBar.click(event); break;
                }
                if(result != nullptr){
                    Position towerPosition = map.generateTowerPosition(Position(event.button.x, event.button.y));
                    addTower(towerPosition, result->getTowerType());

                    if(result->isStart()){
                        generateWave();
                    }
                }

            }

            SDL_RenderClear(rend);

            Position selectedField = Position(-100, -100);

            GameBarObject* isSelected = gameBar.isTowerSelected();
            if(isSelected){
                int x, y;
                SDL_PumpEvents();
                Uint32 btn = SDL_GetMouseState(&x, &y);
                selectedField = Position(x, y);
            }

            map.mapRender(selectedField, isSelected);

            gameBar.render();
            this->engineStep();

            waveEngine.waveStep(map);

            if(noEnemies==0){
                gameStatus_ = gameStatus::waiting;
            }

            SDL_RenderPresent(rend);

            SDL_Delay(1000 / 60);
        }

        gameStatus_ = gameStatus::win;
    };


    void addTower(Position position, enum towers type) {
        Tower *tower = (Tower*) calloc(sizeof (Tower), 1);
        switch (type) {
            case towers::small: *tower = Builder::smallTower(rend, position); break;
            case towers::big: *tower = Builder::bigTower(rend, position); break;
            default: return;
        }
        SDL_QueryTexture(tower->tex, NULL, NULL, &tower->getDest()->w, &tower->getDest()->h);
        towerList.push_back(*tower);
    };

    void engineStep(){
        SDL_Event ev;

        for(auto & tower : towerList){
            tower.render();
            Position towerPosition = tower.getPosition();
            if(!tower.canShoot()){
                continue;
            }
            waveEngine.enemyStep(towerPosition, tower);
        }
    };


    void generateWave(){
        gameStatus_ = gameStatus::wave;
        waveEngine.getWave();
    }

    enum gameStatus getStatus(){
        return gameStatus_;
    }
};

#endif //TOWER_DEFENCE_GAME_LEVELENGINE_H
