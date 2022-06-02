//
// Created by Maciej on 26.05.2022.
//

#include "../headers/Engine.h"


void Engine::start() {
    MenuScreen ms = MenuScreen(rend);
    isRunning = true;

    while (true){
        ms.step();

        SDL_RenderClear(rend);
        ms.render();

        SDL_RenderPresent(rend);

        SDL_Delay(1000 / 10);

        if(ms.isSelected()){
            break;
        }
    }

    *levelEngine = LevelEngine(rend, ms.getLevel());
    levelEngine->start();
    ms.clearChoice();
    while (isRunning){

        enum gameStatus gs = levelEngine->getStatus();
        if(gs == gameStatus::defeat){
            isRunning = false;
        }
        if(gs == gameStatus::win){
            isRunning = false;
        }
        if(gs== gameStatus::menu){
            start();
        }
    }
}
