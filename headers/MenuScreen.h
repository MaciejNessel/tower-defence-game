//
// Created by Maciej on 02.06.2022.
//

#ifndef TOWER_DEFENCE_GAME_MENUSCREEN_H
#define TOWER_DEFENCE_GAME_MENUSCREEN_H

#include "SDL.h"
#include "LevelButton.h"
#include <vector>
#include "Position.h"

class MenuScreen{
    SDL_Renderer* rend;
    std::vector<LevelButton> objects;
    char* lvlName = nullptr;
public:
    MenuScreen(SDL_Renderer* rend)
    :rend(rend){
        addLevel(100, 100, IMG_Load("../images/lvl1.png"), (char*) "../resources/lvl0.txt");
        addLevel(350, 100, IMG_Load("../images/lvl2.png"), (char*) "../resources/lvl2.txt");
    }

    void step(){
        SDL_Event event;
        LevelButton *result = nullptr;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_MOUSEBUTTONDOWN: result = click(event); break;
            }
            if(result != nullptr){
                lvlName = result->getLevelName();
            }
        }
    }

    void addLevel(int x, int y, SDL_Surface* surface, char* name){
        LevelButton toAdd = LevelButton(x, y, rend, surface, name);
        SDL_QueryTexture(toAdd.tex, NULL, NULL, &toAdd.getDest()->w, &toAdd.getDest()->h);
        objects.push_back(toAdd);
    }

    void render(){
        for(int i=0; i<objects.size(); i++){
            objects.at(i).render();
        }
    }

    LevelButton* clickLeftBar(SDL_Event event, Position clickPosition) {
        for(int i=0; i<objects.size(); i++){
            Position objectStartPosition = objects[i].getPosition();
            Position objectEndPosition = Position(objectStartPosition.x() + objects[i].getDest()->w,
                                                  objectStartPosition.y()+objects[i].getDest()->h);
            if(clickPosition.isTargetRectangle(objectStartPosition, objectEndPosition)){
                lvlName = objects[i].getLevelName();
                return &objects[i];
            }
        }
        return nullptr;
    }


    LevelButton* click(SDL_Event event) {
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

    char* getLevel() {
        return lvlName;
    }
};




#endif //TOWER_DEFENCE_GAME_MENUSCREEN_H
