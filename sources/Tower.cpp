//
// Created by Maciej on 26.05.2022.
//

#include "../headers/Tower.h"

void Tower::render() {
    if(respawnCnt < RESPAWN_BALL_TOWER){
        respawnCnt++;
    }
    SDL_RenderCopy(rend, tex, nullptr, &dest);
}

int Tower::getForceAndShoot() {
    int force = 0;
    switch (towerBulletType) {
        case bullets::arrow: force = ARROW_FORCE; break;
        case bullets::ball: force = BULLET_BALL_FORCE; break;
    }
    return force;
}
