//
// Created by Maciej on 26.05.2022.
//
#include "../headers/Enemy.h"
void Enemy::addBullet(Position position, enum bullets bulletType) {
    Bullet *bullet = (Bullet *)calloc(sizeof (Bullet), 1);
    switch (bulletType) {
        case bullets::arrow: *bullet = Bullet(rend, position.x(), position.y(), ARROW_FORCE, ARROW_SPEED, "../images/arrow.png"); break;
        case bullets::ball: *bullet = Bullet(rend, position.x(), position.y(), BULLET_BALL_FORCE, BULLET_BALL_SPEED, "../images/bullet.png"); break;
    }
    SDL_QueryTexture(bullet->tex, NULL, NULL, &bullet->getDest()->w, &bullet->getDest()->h);
    bulletList.push_back(*bullet);
}

void Enemy::rendBullets() {
    for(int i=0; i<bulletList.size(); i++){
        bulletList[i].render();
        bool isArrived = bulletList[i].step(Position(position.x() + dest.w * 0.5, position.y()+dest.h*0.5));
        if(isArrived){
            dealDamage(bulletList[i].getForce());
            bulletList.erase(bulletList.begin()+i);
        }
    }
}

void Enemy::renderLife() {
    Position pos = getPosition();
    for(int i=0; i<hp*0.2; i++){
        SDL_RenderDrawPoint(rend, pos.x() +dest.w*0.25 +i, pos.y());
        SDL_RenderDrawPoint(rend, pos.x() +dest.w*0.25 + i, pos.y()+1);
        SDL_RenderDrawPoint(rend, pos.x() + dest.w*0.25 +i, pos.y()+2);
    }
}

void Enemy::render() {
    SDL_RenderCopy(rend, tex, nullptr, &dest);
    renderLife();
}

bool Enemy::dealDamage(int force) {
    hp -= force;
    return checkAlive();
}
