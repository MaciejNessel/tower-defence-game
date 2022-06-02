//
// Created by Maciej on 17.05.2022.
//

#ifndef TOWER_DEFENCE_GAME_TOWER_H
#define TOWER_DEFENCE_GAME_TOWER_H

#include "MapObject.h"
#include <SDL_image.h>
#include <SDL.h>
#include "Common.h"
#include "Bullet.h"
#include <iostream>

class Tower: public MapObject{
protected:
    int range = 100;
    Position position;
    enum bullets towerBulletType;
    int respawnTime = RESPAWN_BALL_TOWER;
    int respawnCnt = 1;

public:

    Tower(SDL_Renderer* rend, int x, int y, int range, char* img_src, enum bullets bullet)
            :MapObject(x, y, rend, IMG_Load(img_src))
            ,position(Position(x,y))
            ,range(range)
            ,towerBulletType(bullet){
    }

    ~Tower() = default;

    virtual void render();

    int getRange() const{
        return range;
    }

    int getForceAndShoot();

    enum bullets getBulletType(){
        return towerBulletType;
    }

    bool canShoot(){
        bool res = respawnCnt % RESPAWN_BALL_TOWER == 0;
        if(res){
            respawnCnt=0;
        }
        return res;
    }

};


#endif //TOWER_DEFENCE_GAME_TOWER_H
