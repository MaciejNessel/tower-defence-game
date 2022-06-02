//
// Created by Maciej on 02.06.2022.
//

#ifndef TOWER_DEFENCE_GAME_LEVELBUTTON_H
#define TOWER_DEFENCE_GAME_LEVELBUTTON_H
#include "MapObject.h"

class LevelButton: public MapObject{
    char* levelName;
public:
    LevelButton(int x, int y,  SDL_Renderer* rend, SDL_Surface* surface, char* levelName)
    :MapObject(x, y, rend, surface)
    ,levelName(levelName){}

    char* getLevelName(){
        return levelName;
    }

};

#endif //TOWER_DEFENCE_GAME_LEVELBUTTON_H
