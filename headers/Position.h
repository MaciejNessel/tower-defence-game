//
// Created by Maciej on 17.05.2022.
//

#ifndef TOWER_DEFENCE_GAME_POSITION_H
#define TOWER_DEFENCE_GAME_POSITION_H

#include "Directions.h"
#include <cmath>

class Position{
private:
    int posX;
    int posY;

public:
    Position(int x, int y)
    :posX(x)
    ,posY(y){}

    int x(){
        return posX;
    }
    int y(){
        return posY;
    }

    void moveTo(int x, int y);

    void move(Directions dir);

    bool isTargetCircle(Position towerPosition, int towerRadius){
        return pow((towerPosition.x()-posX), 2.0) + pow((towerPosition.y()-posY), 2.0) <= pow(towerRadius, 2.0);
    }

    bool equal(Position position) {
        return position.x() == posX && position.y() == posY;
    }

    bool isTargetRectangle(Position start, Position end) const{
        return posX >= start.x() && posX <= end.x() && posY >= start.y() && posY<=end.y();
    }

    bool operator <( const Position & rightPos );

    bool operator >( const Position & rightPos );
};

#endif //TOWER_DEFENCE_GAME_POSITION_H
