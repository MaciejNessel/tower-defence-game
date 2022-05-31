//
// Created by Maciej on 19.05.2022.
//

#ifndef TOWER_DEFENCE_GAME_BULLET_H
#define TOWER_DEFENCE_GAME_BULLET_H

#include "MapObject.h"
#include "Common.h"


class Bullet: public MapObject{
private:
    int force;
    int speed;

public:
    Bullet(SDL_Renderer* rend, int x, int y)
            :force(BULLET_BALL_FORCE)
            ,MapObject(x, y, rend, IMG_Load("../images/bullet.png"))
            ,speed(BULLET_BALL_SPEED){
    }

    ~Bullet() = default;

    bool step(Position targetPosition);;

    int getForce() const{
        return force;
    }

};



#endif //TOWER_DEFENCE_GAME_BULLET_H
