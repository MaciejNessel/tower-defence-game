//
// Created by Maciej on 26.05.2022.
//

#include "../headers/GameBar.h"

void GameBar::addObject(int x, int y, SDL_Surface *surface) {
    MapObject toAdd = MapObject(x, y, rend, surface);
    SDL_QueryTexture(toAdd.tex, NULL, NULL, &toAdd.getDest()->w, &toAdd.getDest()->h);
    barObjects.push_back(toAdd);
}

void GameBar::render() {
    for(int i=0; i<barObjects.size(); i++){
        barObjects[i].render();

    }
}

MapObject *GameBar::clickLeftBar(SDL_Event event, Position clickPosition) {
    if(clickPosition.isTargetRectangle(Position(0,0), Position(MAP_WIDTH, MAP_HEIGHT))){
        MapObject* result = selected;\
            selected = nullptr;
        return result;
    }
    for(int i=0; i<barObjects.size(); i++){
        Position objectStartPosition = barObjects[i].getPosition();
        Position objectEndPosition = Position(objectStartPosition.x() + barObjects[i].getDest()->w,
                                              objectStartPosition.y()+barObjects[i].getDest()->h);
        if(clickPosition.isTargetRectangle(objectStartPosition, objectEndPosition)){
            selected = &barObjects[i];
        }
    }
    return nullptr;
}

MapObject *GameBar::clickRight(SDL_Event event) {
    selected = nullptr;
    return selected;
}

MapObject *GameBar::click(SDL_Event event) {
    Position clickPosition(event.button.x, event.button.y);
    MapObject * result;
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

bool GameBar::isSelected() {
    if(selected!= nullptr){
        return true;
    }
    return false;
}
