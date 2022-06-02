//
// Created by Maciej on 27.05.2022.
//

#include "../headers/Map.h"

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
    std::ifstream myfile (lvl_name);
    std::string line;
    if (myfile.is_open())
    {
        int cnt = 0;
        while ( std::getline (myfile, line) )
        {
            std::vector<std::string> words = splitBySpace(line);

            switch (cnt) {
                case 0:
                    start = Position(std::stoi(words.at(0)) * NO_BACKGROUND_SIZE, std::stoi(words.at(1))* NO_BACKGROUND_SIZE);
                    break;
                case 1:
                    end = Position(std::stoi(words.at(0))* NO_BACKGROUND_SIZE, std::stoi(words.at(1))* NO_BACKGROUND_SIZE);
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

Position Map::generateCenterPosition(Position position) {
    Position insertOn = Position(floor(position.x()/BLOCK_BACKGROUND_SIZE)*BLOCK_BACKGROUND_SIZE, floor(position.y()/BLOCK_BACKGROUND_SIZE)*BLOCK_BACKGROUND_SIZE);
    return insertOn;
}

void Map::renderSelectedTowerOnMap(Position selectedPosition, GameBarObject* selectedTower) {
    if(selectedPosition<Position(0,0) || Position(height*BLOCK_BACKGROUND_SIZE, width*BLOCK_BACKGROUND_SIZE)<selectedPosition){
        return;
    }
    int range = 0;
    SDL_Surface *towerSurface = (SDL_Surface*) calloc(sizeof (SDL_Surface*), 1);
    switch (selectedTower->getTowerType()) {
        case towers::small:
            towerSurface = IMG_Load("../images/tower.png");
            range = SMALL_TOWER_RANGE;
            break;
        case towers::big:
            towerSurface = IMG_Load("../images/tower2.png");
            range = BIG_TOWER_RANGE;
            break;
        default: return;
    }
    Position insertOn = generateCenterPosition(selectedPosition);

    MapObject tower = MapObject(insertOn.x(), insertOn.y(), rend, towerSurface);
    SDL_Circle::Draw(rend, insertOn.x()+50, insertOn.y()+50, range);
    SDL_QueryTexture(tower.tex, NULL, NULL, &tower.getDest()->w, &tower.getDest()->h);
    tower.render();
}

void Map::mapRender(Position selectedPosition, GameBarObject* selectedTower) {
    for(int i=0; i<mapBackground.size(); i++){
        mapBackground.at(i).render();
    }
    renderSelectedTowerOnMap(selectedPosition, selectedTower);
}

Position Map::getStart() {
    return this->start;
}

Position Map::getEnd() {
    return this->end;
}

int **Map::getMap() const {
    return this->map;
}

bool Map::canMove(Position position) const {
    return map[position.x()][position.y()];
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

Position Map::generateTowerPosition(Position mousePosition) {
    return generateCenterPosition(mousePosition);
}
