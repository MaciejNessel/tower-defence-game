//
// Created by Maciej on 17.05.2022.
//

#ifndef TOWER_DEFENCE_GAME_COMMON_H
#define TOWER_DEFENCE_GAME_COMMON_H

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define MAP_WIDTH 600
#define MAP_HEIGHT 600

#define BLOCK_BACKGROUND_SIZE 25
#define NO_BACKGROUND_SIZE 24

#define BULLET_BALL_FORCE 30
#define BULLET_BALL_SPEED 4
#define ARROW_FORCE 20
#define ARROW_SPEED 10

#define SMALL_TOWER_RANGE 100
#define BIG_TOWER_RANGE 150

#define RESPAWN_BALL_TOWER 30

#define ENEMY_FIRST_HP 100


#define START_MONEY 200

enum bullets{
    ball, arrow
};

enum towers{
    small, big
};

enum gameStatus{
    win, defeat, waiting, wave, menu
};

#endif //TOWER_DEFENCE_GAME_COMMON_H
