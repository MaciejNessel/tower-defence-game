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
#include <string>
#include "Common.h"
#include "GameBarObject.h"
#include "SDL_Circle.h"

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

    Position generateCenterPosition(Position position);

    void renderSelectedTowerOnMap(Position selectedPosition, GameBarObject* selectedTower);

    void mapRender(Position selectedPosition, GameBarObject* selectedTower);

    Position getStart();

    Position getEnd();

    int **getMap() const;

    bool canMove(Position position) const;

    bool isEnd(Position position);

    Directions nextEnemyStep(Position position);

    Position generateTowerPosition(Position mousePosition);

};
#endif //TOWER_DEFENCE_GAME_MAP_H
