//
// Created by Maciej on 26.05.2022.
//

#include "../headers/GameBar.h"

void GameBar::addObject(int x, int y, SDL_Surface *surface, bool isStart) {
    GameBarObject toAdd = GameBarObject(x, y, rend, surface);
    if(isStart){
        toAdd.setStart();
    }
    SDL_QueryTexture(toAdd.tex, NULL, NULL, &toAdd.getDest()->w, &toAdd.getDest()->h);
    barObjects.push_back(toAdd);
}

void GameBar::addTower(int x, int y, SDL_Surface *surface, enum towers type) {
    GameBarObject toAdd = GameBarObject(x, y, rend, surface);
    toAdd.setTowerType(type);
    SDL_QueryTexture(toAdd.tex, NULL, NULL, &toAdd.getDest()->w, &toAdd.getDest()->h);
    barObjects.push_back(toAdd);
}

void GameBar::render() {
    for(int i=0; i<barObjects.size(); i++){
        barObjects[i].render();

    }
}

GameBarObject *GameBar::clickLeftBar(SDL_Event event, Position clickPosition) {
    if(clickPosition.isTargetRectangle(Position(0,0), Position(MAP_WIDTH, MAP_HEIGHT))){
        GameBarObject* result = selected;
        selected = nullptr;
        return result;
    }
    for(int i=0; i<barObjects.size(); i++){
        Position objectStartPosition = barObjects[i].getPosition();
        Position objectEndPosition = Position(objectStartPosition.x() + barObjects[i].getDest()->w,
                                              objectStartPosition.y()+barObjects[i].getDest()->h);
        if(clickPosition.isTargetRectangle(objectStartPosition, objectEndPosition)){
            if(barObjects[i].isStart()){
                return &barObjects[i];
            }
            selected = &barObjects[i];
        }
    }
    return nullptr;
}

GameBarObject *GameBar::clickRight(SDL_Event event) {
    selected = nullptr;
    return selected;
}

GameBarObject *GameBar::click(SDL_Event event) {
    Position clickPosition(event.button.x, event.button.y);
    GameBarObject * result;
    switch (event.button.button) {
        case SDL_BUTTON_LEFT:
            result=clickLeftBar(event, clickPosition);
            break;
        case SDL_BUTTON_RIGHT:
            result=clickRight(event);
            break;
    }
    return result;

}

GameBarObject* GameBar::isTowerSelected() {
    return selected;
}
