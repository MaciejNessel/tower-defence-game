//
// Created by Maciej on 17.05.2022.
//

#ifndef TOWER_DEFENCE_GAME_ENEMY_H
#define TOWER_DEFENCE_GAME_ENEMY_H

#include "MapObject.h"
#include <vector>
#include "Bullet.h"
#include "Common.h"

class Enemy: public MapObject{
private:
    std::vector<Bullet> bulletList;
public:
    int virtualHp;
    int hp;

    Enemy(SDL_Renderer* rend, int x, int y)
    :hp(ENEMY_FIRST_HP)
    ,MapObject(x, y, rend, IMG_Load("../images/enemy.png"))
    ,virtualHp(ENEMY_FIRST_HP){
    }

    bool checkAlive() const{
        if(hp<0){
            SDL_DestroyTexture(tex);
        }
        return hp>0;
    }
    bool dealDamage(int force);
//    ~Enemy() = default;
    void dealVirtualDamage(int force) {
        virtualHp -= force;
    }
    void addBullet(Position position, enum bullets bulletType);
    void rendBullets();
    void render();
    void renderLife();
};



#endif //TOWER_DEFENCE_GAME_ENEMY_H
