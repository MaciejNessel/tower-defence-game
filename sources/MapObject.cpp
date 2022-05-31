//
// Created by Maciej on 26.05.2022.
//

#include "../headers/MapObject.h"

void MapObject::moveTo(int x, int y) {
    this->position.moveTo(x, y);
    this->updateDest();
}

void MapObject::move(Directions dir) {
    this->position.move(dir);
    this->updateDest();
}
