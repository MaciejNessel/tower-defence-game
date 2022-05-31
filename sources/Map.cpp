//
// Created by Maciej on 26.05.2022.
//

#include "../headers/Map.h"
#include "../headers/Common.h"

void Map::loadBackgroundTextures() {
    for (int i=0; i<height; i++){
        for (int j=0; j<width; j++){
            switch (map[i][j]) {
                case 0: addGrass(Position(i*BLOCK_BACKGROUND_SIZE, j*BLOCK_BACKGROUND_SIZE)); break;
                case 1: addRoad(Position(i*BLOCK_BACKGROUND_SIZE, j*BLOCK_BACKGROUND_SIZE)); break;
            }

        }
    }
}

std::vector<std::string> Map::splitBySpace(std::string line) {
    std::string space_delimiter = " ";
    std::vector<std::string> words{};
    size_t pos = 0;
    size_t lastPos = 0;
    while ((pos = line.find(space_delimiter)) != std::string::npos) {
        words.push_back(line.substr(0, pos));
        line.erase(0, pos + space_delimiter.length());
        lastPos = pos;
    }
    words.push_back(line.substr(fmax(0, lastPos-1), line.size()));
    return words;
}

void Map::loadLevelMap(std::vector<std::string> line, int j) {
    int i = 0;
    for (const auto &letter : line) {
        switch (letter[0]) {
            case 'G': map[i][j] = 0; break;
            default: map[i][j] = 1; break;
        }
        mapDirections[i][j] = letter;
        i++;
    }
}

void Map::loadLevel() {
    std::ifstream myfile ("../resources/lvl0.txt");
    std::string line;
    if (myfile.is_open())
    {
        int cnt = 0;
        while ( std::getline (myfile, line) )
        {
            std::vector<std::string> words = splitBySpace(line);

            switch (cnt) {
                case 0:
                    start = Position(std::stoi(words.at(0)), std::stoi(words.at(1)));
                    break;
                case 1:
                    end = Position(std::stoi(words.at(0)), std::stoi(words.at(1)));
                    break;
                default:
                    loadLevelMap(words, cnt - 2);
            }
            cnt++;
        }
        myfile.close();
    }
    myfile.close();
}

void Map::addGrass(Position position) {
    Grass grass = Grass(rend, position.x(), position.y());
    SDL_QueryTexture(grass.tex, NULL, NULL, &grass.getDest()->w, &grass.getDest()->h);
    mapBackground.push_back(grass);
}

void Map::addRoad(Position position) {
    Road road = Road(rend, position.x(), position.y());
    SDL_QueryTexture(road.tex, NULL, NULL, &road.getDest()->w, &road.getDest()->h);
    mapBackground.push_back(road);
}

void Map::mapRender(Position selectedPosition) {
    for(int i=0; i<mapBackground.size(); i++){
        mapBackground.at(i).render();
    }
    MapObject ok = MapObject(selectedPosition.x(), selectedPosition.y(), rend, IMG_Load("../images/ok.png"));
    SDL_QueryTexture(ok.tex, NULL, NULL, &ok.getDest()->w, &ok.getDest()->h);
    ok.render();
}

bool Map::isEnd(Position position) {
    int blockX = position.x() / 25;
    int blockY = position.y() / 25;
    return end.equal(Position(blockX, blockY));
}

Directions Map::nextEnemyStep(Position position) {
    Directions result;
    switch (mapDirections[position.x()][position.y()][0]) {
        case 'N': result = Directions::N; break;
        case 'S': result = Directions::S; break;
        case 'E': result = Directions::E; break;
        case 'W': result = Directions::W; break;
    }
    return result;
}
