//
// Created by Maciej on 02.06.2022.
//

#ifndef TOWER_DEFENCE_GAME_MENUSCREEN_H
#define TOWER_DEFENCE_GAME_MENUSCREEN_H

#include "SDL.h"
#include "LevelButton.h"
#include <vector>
#include "Position.h"
#include <iostream>

class MenuScreen{
    SDL_Renderer* rend;
    std::vector<LevelButton> objects;
    char* lvlName = (char*) calloc(sizeof (char ),256);
    bool isSelectedLevel = false;
    MapObject logo;
public:
    MenuScreen(SDL_Renderer* rend)
    :rend(rend)
    , logo(MapObject(200, 50,rend, IMG_Load("../images/logo.png"))){

        SDL_QueryTexture(logo.tex, NULL, NULL, &logo.getDest()->w, &logo.getDest()->h);

        addLevel(100, 240, IMG_Load("../images/lvl1.png"), (char*) "../resources/lvl0.txt");
        addLevel(450, 240, IMG_Load("../images/lvl2.png"), (char*) "../resources/lvl2.txt");
    }

    ~MenuScreen(){
        logo.destroy();
        for(int i=0; i<objects.size(); i++){
            objects.at(i).destroy();
        }
        objects.clear();
        free(lvlName);
    }

    void step();

    void addLevel(int x, int y, SDL_Surface* surface, char* name);

    void render();

    LevelButton* clickLeftBar(SDL_Event event, Position clickPosition);


    LevelButton* click(SDL_Event event);

    char* getLevel() {
        return lvlName;
    }

    void clearChoice(){
        lvlName = nullptr;
        isSelectedLevel = false;
    }

    bool isSelected(){
        return isSelectedLevel;
    }
};




#endif //TOWER_DEFENCE_GAME_MENUSCREEN_H
