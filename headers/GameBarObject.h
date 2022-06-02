
//
// Created by Maciej on 01.06.2022.
//

#ifndef TOWER_DEFENCE_GAME_GAMEBAROBJECT_H
#define TOWER_DEFENCE_GAME_GAMEBAROBJECT_H
#include "MapObject.h"
#include "Common.h"

class GameBarObject : public MapObject{
private:
    bool isTower_ = false;
    enum towers towerType;

    bool isStart_ = false;

public:
    GameBarObject(int x, int y,  SDL_Renderer* rend, SDL_Surface* surface)
    :MapObject(x, y, rend, surface){}

    bool isTower(){
        return isTower_;
    }

    enum towers getTowerType(){
        return towerType;
    }

    void setTowerType(enum towers type){
        isTower_ = true;
        towerType = type;
    }

    virtual void render(){
        SDL_RenderCopy(rend, tex, nullptr, &dest);
    }

    void setStart(){
        this->isStart_ = true;
    }

    bool isStart(){
        return isStart_;
    }
};

#endif //TOWER_DEFENCE_GAME_GAMEBAROBJECT_H
