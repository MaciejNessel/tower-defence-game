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

class GameBar{
private:
    int money;
    bool isRunning;
    GameBarObject *selected;
    std::vector<GameBarObject> barObjects;
    SDL_Renderer* rend;

public:
    GameBar(SDL_Renderer* rend)
    :money(START_MONEY)
    ,isRunning(false)
    ,selected(nullptr)
    ,rend(rend){
        addTower(MAP_WIDTH, 0, IMG_Load("../images/tower.png"), towers::small);
        addTower(MAP_WIDTH, 150, IMG_Load("../images/tower2.png"), towers::big);
        addObject(MAP_WIDTH, 300, IMG_Load("../images/start.png"), true);
    }

    void addObject(int x, int y, SDL_Surface* surface, bool isStart);

    void addTower(int x, int y, SDL_Surface* surface, enum towers type);

    void render();

    GameBarObject * clickLeftBar(SDL_Event event, Position clickPosition);

    GameBarObject * clickRight(SDL_Event event);

    GameBarObject * click(SDL_Event event);

    GameBarObject* isTowerSelected();

};

#endif //TOWER_DEFENCE_GAME_GAMEBAR_H
