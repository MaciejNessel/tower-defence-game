//
// Created by Maciej on 19.05.2022.
//

#include "../headers/Bullet.h"


bool Bullet::step(Position targetPosition) {
    int directionX = (targetPosition.x()<position.x()) ? -1 : 1;
    int directionY = (targetPosition.y()<position.y()) ? -1 : 1;

    int absX = abs(targetPosition.x() - position.x());
    int absY = abs(targetPosition.y() - position.y());

    int distance = (int)(sqrt(absX*absX + absY*absY));
    if(distance==0)
        return true;

    double cosAlpha = (double)absX / distance;
    double sinAlpha = (double)absY / distance;

    int nextX = position.x() + ceil((double) speed * cosAlpha) * directionX;
    int nextY = position.y() + ceil((double) speed * sinAlpha) * directionY;

    moveTo(nextX, nextY);

    if(targetPosition.isTargetCircle(position, 20)){
        return true;
    }

    return false;
}
