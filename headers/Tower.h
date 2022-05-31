//
// Created by Maciej on 17.05.2022.
//

#ifndef TOWER_DEFENCE_GAME_TOWER_H
#define TOWER_DEFENCE_GAME_TOWER_H

#include "MapObject.h"
#include <SDL_image.h>
#include <SDL.h>
#include "Common.h"

//int SDL_RenderDrawCircle(SDL_Renderer * renderer, int x, int y, int radius)
//{
//    int offsetx, offsety, d;
//    int status;
//
//    offsetx = 0;
//    offsety = radius;
//    d = radius -1;
//    status = 0;
//
//    while (offsety >= offsetx) {
//        status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
//        status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
//        status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
//        status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
//        status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
//        status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
//        status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
//        status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);
//
//        if (status < 0) {
//            status = -1;
//            break;
//        }
//
//        if (d >= 2*offsetx) {
//            d -= 2*offsetx + 1;
//            offsetx +=1;
//        }
//        else if (d < 2 * (radius - offsety)) {
//            d += 2 * offsety - 1;
//            offsety -= 1;
//        }
//        else {
//            d += 2 * (offsety - offsetx - 1);
//            offsety -= 1;
//            offsetx += 1;
//        }
//    }
//
//    return status;
//}

class Tower: public MapObject{
private:
    int range = 100;
    int force = 30;
    Position position;

    int respawnTime = RESPAWN_BALL_TOWER;
    int currentStatus = 0;

public:
    int canShoot = true;
    Tower(SDL_Renderer* rend, int x, int y)
            :MapObject(x, y, rend, IMG_Load("../images/tower.png"))
            ,position(Position(x,y)){
    }

    ~Tower() = default;

    virtual void render();

    int getRange() const{
        return range;
    }

    int getForce() const {
        return force;
    }

    int getForceAndShoot();
};


#endif //TOWER_DEFENCE_GAME_TOWER_H
