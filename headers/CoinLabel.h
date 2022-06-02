//
// Created by Maciej on 02.06.2022.
//

#ifndef TOWER_DEFENCE_GAME_COINLABEL_H
#define TOWER_DEFENCE_GAME_COINLABEL_H
#include "MapObject.h"
#include <SDL2/SDL_ttf.h>
#include "../headers/Common.h"
#include <iostream>
#include <sstream>


class CoinLabel : public MapObject{
    SDL_Renderer* rend;
    int x, y;
    int countNum;
public:

    CoinLabel(int x, int y, int money, SDL_Renderer* rend)
    :MapObject(x, y, rend, IMG_Load("../images/coin.png"))
    ,rend(rend)
    ,x(x)
    ,y(y)
    ,countNum(money){
    }

    void render(){
        MapObject coin = MapObject(x, y, rend, IMG_Load("../images/coin.png"));
        SDL_QueryTexture(coin.tex, NULL, NULL, &coin.getDest()->w, &coin.getDest()->h);
        coin.render();

        TTF_Font* Arial;
        TTF_Init();
        Arial = TTF_OpenFont("../assets/arial.ttf", 24);
        if(!Arial) {
            return;
        }
        SDL_Color White = {255, 255, 255};

        std::stringstream ss;
        ss << countNum;
        std::string a;
        ss >> a;

        MapObject count = MapObject(x+25, y+0, rend, TTF_RenderText_Solid(Arial, a.c_str(), White));
        SDL_QueryTexture(count.tex, NULL, NULL, &count.getDest()->w, &count.getDest()->h);

        count.render();
    }

    void updateCount(int num){
        countNum = num;
    }

};

#endif //TOWER_DEFENCE_GAME_COINLABEL_H
