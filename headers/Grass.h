//
// Created by Maciej on 17.05.2022.
//

#ifndef TOWER_DEFENCE_GAME_GRASS_H
#define TOWER_DEFENCE_GAME_GRASS_H
#include "MapObject.h"
#include <SDL_image.h>
#include <SDL.h>

class Grass : public MapObject{
public:
    Grass(SDL_Renderer* rend, int x, int y)
    :MapObject(x, y, rend, IMG_Load("../images/grass.png")){

    }

    ~Grass() = default;
};

#endif //TOWER_DEFENCE_GAME_GRASS_H
