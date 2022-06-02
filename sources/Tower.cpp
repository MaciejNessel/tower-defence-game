//
// Created by Maciej on 26.05.2022.
//

#include "../headers/Tower.h"

void Tower::render() {
    currentStatus++;
    currentStatus %= respawnTime;
    if(currentStatus==0){
        canShoot = true;
    }
    SDL_RenderCopy(rend, tex, nullptr, &dest);
//    SDL_RenderDrawCircle(rend, position.x()+dest.w*0.5, position.y()+dest.h*0.5, range);
}

int Tower::getForceAndShoot() {
    canShoot = false;
    int force = 0;
    switch (towerBulletType) {
        case bullets::arrow: force = ARROW_FORCE; break;
        case bullets::ball: force = BULLET_BALL_FORCE; break;
    }
    return force;
}
