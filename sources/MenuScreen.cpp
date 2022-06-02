//
// Created by Maciej on 02.06.2022.
//

#include "../headers/MenuScreen.h"


void MenuScreen::step() {
    SDL_Event event;
    LevelButton *result = nullptr;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                exit(0);
            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {
                    case SDL_BUTTON_LEFT:
                        result = click(event); break;
                        break;
                    case SDL_BUTTON_RIGHT:
                        return;
                }
        }
        if(result != nullptr){
            lvlName = result->getLevelName();
        }
    }
}

void MenuScreen::addLevel(int x, int y, SDL_Surface *surface, char *name) {
    LevelButton toAdd = LevelButton(x, y, rend, surface, name);
    SDL_QueryTexture(toAdd.tex, NULL, NULL, &toAdd.getDest()->w, &toAdd.getDest()->h);
    objects.push_back(toAdd);
}

void MenuScreen::render() {
    for(int i=0; i<objects.size(); i++){
        objects.at(i).render();
    }
    logo.render();
}

LevelButton *MenuScreen::clickLeftBar(SDL_Event event, Position clickPosition) {
    for(int i=0; i<objects.size(); i++){
        Position objectStartPosition = objects[i].getPosition();
        Position objectEndPosition = Position(objectStartPosition.x() + objects[i].getDest()->w,
                                              objectStartPosition.y()+objects[i].getDest()->h);
        if(clickPosition.isTargetRectangle(objectStartPosition, objectEndPosition)){
            if(objects.at(i).getLevelName()==""){
                continue;
            }

            strcpy(lvlName, objects[i].getLevelName());
            isSelectedLevel = true;
            return &objects[i];
        }
    }
    return nullptr;
}

LevelButton *MenuScreen::click(SDL_Event event) {
    Position clickPosition(event.button.x, event.button.y);
    LevelButton * result;
    switch (event.button.button) {
        case SDL_BUTTON_LEFT:
            result=clickLeftBar(event, clickPosition);
            break;
        case SDL_BUTTON_RIGHT:
            break;
    }
    return result;
}
