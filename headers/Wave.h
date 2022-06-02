//
// Created by Maciej on 02.06.2022.
//

#ifndef TOWER_DEFENCE_GAME_WAVE_H
#define TOWER_DEFENCE_GAME_WAVE_H


class Wave{
public:
    int enemies, force, speed;
    Wave(int numberOfEnemies, int force, int speed)
    :enemies(numberOfEnemies)
    ,force(force)
    ,speed(speed){
    }
};
#endif //TOWER_DEFENCE_GAME_WAVE_H
