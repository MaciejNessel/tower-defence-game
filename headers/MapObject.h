//
// Created by Maciej on 17.05.2022.
//

#ifndef TOWER_DEFENCE_GAME_MAPOBJECT_H
#define TOWER_DEFENCE_GAME_MAPOBJECT_H
#include <SDL.h>
#include "Directions.h"
#include "Position.h"
#include <SDL_image.h>
#include <iostream>

class MapObject{
protected:
    Position position;
    SDL_Rect dest{};
    bool isRoad_ = false;
private:
    void updateDest(){
        this->dest.x = position.x();
        this->dest.y = position.y();
    }

public:
    SDL_Texture* tex;
    SDL_Renderer* rend;

    MapObject(int x, int y, SDL_Renderer* rend, SDL_Surface* surface)
        :position(Position(x, y))
        ,rend(rend){
        dest.x = x;
        dest.y = y;
        this->tex = SDL_CreateTextureFromSurface(rend, surface);
        SDL_FreeSurface(surface);
    }

    ~MapObject(){
    }


    virtual void render(){
        SDL_RenderCopy(rend, tex, nullptr, &dest);
    }

    Position getPosition(){
        return position;
    }

    Position getCenterPosition(){
        return Position(position.x()+dest.w*0.5, position.y()+dest.h*0.5);
    }

    void moveTo(int x, int y);

    void move(Directions dir);

    SDL_Rect* getDest(){
        return &dest;
    }

    void setRoad(){
        isRoad_ = true;
    }
    bool isRoad(){
        return isRoad_;
    }

};

#endif //TOWER_DEFENCE_GAME_MAPOBJECT_H
