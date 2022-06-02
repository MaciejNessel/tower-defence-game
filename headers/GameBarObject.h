
//
// Created by Maciej on 01.06.2022.
//

#ifndef TOWER_DEFENCE_GAME_GAMEBAROBJECT_H
#define TOWER_DEFENCE_GAME_GAMEBAROBJECT_H
#include "MapObject.h"
#include "Common.h"
#include "CoinLabel.h"

class GameBarObject : public MapObject{
private:
    bool isTower_ = false;
    enum towers towerType;
    CoinLabel cl;
    bool isStart_ = false;

public:
    GameBarObject(int x, int y,  SDL_Renderer* rend, SDL_Surface* surface)
    :MapObject(x, y, rend, surface)
    ,cl(CoinLabel(x, y+100, 1100, rend)){
    }

    bool isTower(){
        return isTower_;
    }

    enum towers getTowerType(){
        return towerType;
    }

    void setTowerType(enum towers type){
        isTower_ = true;
        towerType = type;
        switch (type) {
            case towers::small: cl.updateCount(SMALL_TOWER_COST); break;
            case towers::big: cl.updateCount(BIG_TOWER_COST); break;
        }
    }

    virtual void render(){
        if(isTower_){
            cl.render();
        }
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
