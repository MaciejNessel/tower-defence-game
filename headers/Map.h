//
// Created by Maciej on 17.05.2022.
//

#ifndef TOWER_DEFENCE_GAME_MAP_H
#define TOWER_DEFENCE_GAME_MAP_H

#include "Grass.h"
#include "Road.h"
#include <vector>
#include "Position.h"
#include <iostream>
#include <fstream>
#include "Common.h"
#include <string>

class Map{
private:
    int width;
    int height;
    std::vector<MapObject> mapBackground;
    SDL_Renderer* rend;
    Position start = Position(0, 0);
    Position end = Position(0, 0);
public:
    int **map;
    std::string **mapDirections;

    Map(SDL_Renderer* rend)
    :rend(rend)
    ,height(NO_BACKGROUND_SIZE)
    ,width(NO_BACKGROUND_SIZE){

        map = new int* [height];
        mapDirections = new std::string*[height];
        for(int i=0; i<height; i++) {
            map[i] = new int[width];
            mapDirections[i] = new std::string[width];
        }

        loadLevel();
        loadBackgroundTextures();
    }

    void loadBackgroundTextures();

    std::vector<std::string> splitBySpace(std::string line);

    void loadLevelMap(std::vector<std::string> line, int j);

    void loadLevel();

    void addGrass(Position position);

    void addRoad(Position position);

    void mapRender(Position selectedPosition);

    Position getStart(){
        return this->start;
    }

    Position getEnd(){
        return this->end;
    }

    int **getMap() const{
        return this->map;
    }

    bool canMove(Position position) const{
        return map[position.x()][position.y()];
    }

    bool isEnd(Position position);

    Directions nextEnemyStep(Position position);
};
#endif //TOWER_DEFENCE_GAME_MAP_H
