//
// Created by Maciej on 17.05.2022.
//

#ifndef TOWER_DEFENCE_GAME_ROAD_H
#define TOWER_DEFENCE_GAME_ROAD_H

#include "MapObject.h"
#include <SDL_image.h>
#include <SDL.h>


class Road : public MapObject{
public:
    Road(SDL_Renderer* rend, int x, int y)
            :MapObject(x, y, rend, IMG_Load("../images/road.png")){

    }

    ~Road() = default;
};

#endif //TOWER_DEFENCE_GAME_ROAD_H
