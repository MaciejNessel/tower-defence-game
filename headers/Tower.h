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


class Tower: public MapObject{
protected:
    int range = 100;
    Position position;
    enum bullets towerBulletType;
    int respawnTime = RESPAWN_BALL_TOWER;
    int currentStatus = 0;

public:
    int canShoot = true;
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

};


#endif //TOWER_DEFENCE_GAME_TOWER_H
