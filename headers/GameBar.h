//
// Created by Maciej on 18.05.2022.
//

#ifndef TOWER_DEFENCE_GAME_GAMEBAR_H
#define TOWER_DEFENCE_GAME_GAMEBAR_H

#include "MapObject.h"
#include "Common.h"
#include "GameBarObject.h"
#include <vector>
#include <SDL.h>
#include <iostream>
#include "CoinLabel.h"

class GameBar{
private:
    int money;
    bool isRunning;
    GameBarObject *selected;
    std::vector<GameBarObject> barObjects;
    SDL_Renderer* rend;
    GameBarObject backButton = GameBarObject(MAP_WIDTH-100, 22, rend, IMG_Load("../images/back.png"));
    bool back = false;

public:
    GameBar(SDL_Renderer* rend)
    :money(START_MONEY)
    ,isRunning(false)
    ,selected(nullptr)
    ,rend(rend){
        addTower(MAP_WIDTH+50, 0, IMG_Load("../images/tower.png"), towers::small);
        addTower(MAP_WIDTH+50, 150, IMG_Load("../images/tower2.png"), towers::big);
        addObject(MAP_WIDTH+20, 300, IMG_Load("../images/start.png"), true);
        SDL_QueryTexture(backButton.tex, NULL, NULL, &backButton.getDest()->w, &backButton.getDest()->h);
    }

    void addObject(int x, int y, SDL_Surface* surface, bool isStart);

    void addTower(int x, int y, SDL_Surface* surface, enum towers type);

    bool render();

    GameBarObject * clickLeftBar(SDL_Event event, Position clickPosition);

    GameBarObject * clickRight(SDL_Event event);

    GameBarObject * click(SDL_Event event);

    GameBarObject* isTowerSelected();

};

#endif //TOWER_DEFENCE_GAME_GAMEBAR_H
