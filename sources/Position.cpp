//
// Created by Maciej on 26.05.2022.
//
#include "../headers/Position.h"

void Position::moveTo(int x, int y) {
    this->posX = x;
    this->posY = y;
}

void Position::move(Directions dir) {
    switch (dir) {
        case Directions::N: posY--; break;
        case Directions::NE: posY--; posX++; break;
        case Directions::E: posX++; break;
        case Directions::SE: posX++; posY++; break;
        case Directions::S: posY++; break;
        case Directions::SW: posY++; posX--; break;
        case Directions::W: posX--; break;
        case Directions::NW: posX--; posY--; break;
    }
}
