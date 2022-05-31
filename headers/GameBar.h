//
// Created by Maciej on 18.05.2022.
//

#ifndef TOWER_DEFENCE_GAME_GAMEBAR_H
#define TOWER_DEFENCE_GAME_GAMEBAR_H

#include "MapObject.h"
#include "Common.h"

#include <vector>
#include <SDL.h>

class GameBar{
private:
    int money;
    bool isRunning;
    MapObject *selected;
    std::vector<MapObject> barObjects;
    SDL_Renderer* rend;

public:
    GameBar(SDL_Renderer* rend)
    :money(START_MONEY)
    ,isRunning(false)
    ,selected(nullptr)
    ,rend(rend){
        addObject(MAP_WIDTH, 0, IMG_Load("../images/tower.png"));
    }

    void addObject(int x, int y, SDL_Surface* surface);

    void render();

    MapObject * clickLeftBar(SDL_Event event, Position clickPosition);

    MapObject * clickRight(SDL_Event event);

    MapObject * click(SDL_Event event);

    bool isSelected();

};

#endif //TOWER_DEFENCE_GAME_GAMEBAR_H
