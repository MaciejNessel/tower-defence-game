//
// Created by Maciej on 26.05.2022.
//

#include "../headers/Engine.h"


void Engine::start() {
    auto *ms = new MenuScreen(rend);
    isRunning = true;

    while (true){
        ms->step();
        SDL_RenderClear(rend);
        ms->render();
        SDL_RenderPresent(rend);
        SDL_Delay(1000 / 10);
        if(ms->isSelected()){break;}
    }

    auto* levelEngine = new LevelEngine(rend, ms->getLevel());
    levelEngine->start();
    ms->clearChoice();

    delete ms;

    while (isRunning){
        *gs = levelEngine->getStatus();
        if(*gs == gameStatus::defeat){
            isRunning = false;
        }
        else if(*gs == gameStatus::win){
            isRunning = false;
        }
        else if(*gs == gameStatus::menu){
            break;
        }
    }
    delete levelEngine;
    if(*gs == gameStatus::menu){
        start();
    }
}
