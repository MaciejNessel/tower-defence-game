//
// Created by Maciej on 26.05.2022.
//

#include "../headers/Engine.h"


void Engine::start() {

    isRunning = true;
    MenuScreen ms = MenuScreen(rend);
    while (isRunning){
        SDL_RenderClear(rend);
        ms.render();
        ms.step();

        SDL_RenderPresent(rend);

        SDL_Delay(1000 / 60);

        if(ms.getLevel()){
            break;
        }
    }

    *levelEngine = LevelEngine(rend, ms.getLevel());
    levelEngine->start();

    while (isRunning){
        enum gameStatus gs = levelEngine->getStatus();
        if(gs == gameStatus::defeat){
            isRunning = false;
            std::cout<<"Przegrana";
        }
        if(gs == gameStatus::win){
            isRunning = false;
            std::cout<<"Wygrana";
        }
    }
}
