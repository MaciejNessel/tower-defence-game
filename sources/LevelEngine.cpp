//
// Created by Maciej on 02.06.2022.
//

#include "../headers/LevelEngine.h"

void LevelEngine::start() {
    int timer = 0;
    SDL_Event event;
    GameBarObject *result = nullptr;

    while (isRunning){
        if(waveEngine.getEndStatus()){
            victoryScreen();
        }
        timer ++;
        SDL_Event event;
        GameBarObject *result = nullptr;

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: isRunning = false; break;
                case SDL_MOUSEBUTTONDOWN:
                    result = gameBar.click(event);
                    break;
            }
            if(result != nullptr){
                Position towerPosition = map.generateTowerPosition(Position(event.button.x, event.button.y));
                addTower(towerPosition, result->getTowerType());

                if(result->isStart()){
                    generateWave();
                }
            }
        }

        SDL_RenderClear(rend);

        Position selectedField = Position(-100, -100);

        GameBarObject* isSelected = gameBar.isTowerSelected();
        if(isSelected){
            int x, y;
            SDL_PumpEvents();
            Uint32 btn = SDL_GetMouseState(&x, &y);
            selectedField = Position(x, y);
        }

        map.mapRender(selectedField, isSelected);

        if(gameBar.render()){
            gameStatus_ = gameStatus::menu;
            return;
        }
        this->engineStep();

        if(waveEngine.waveStep(map, &coins) == gameStatus::defeat){
            gameStatus_ = gameStatus::defeat;
            defeatScreen();
        }

        if(noEnemies==0){
            gameStatus_ = gameStatus::waiting;
        }

        SDL_RenderPresent(rend);

        SDL_Delay(1000 / 60);


    }

    gameStatus_ = gameStatus::win;
}

bool LevelEngine::isOccupied(Position position){
    for(int i=0; i<towerList.size(); i++){
        if(towerList.at(i).getPosition().equal(position)){
            return true;
        }
    }
    return false;
}

void LevelEngine::addTower(Position position, enum towers type) {
    if(isOccupied(position)){return;}

    Tower *tower = (Tower*) calloc(sizeof (Tower), 1);

    switch (type) {
        case towers::small: *tower = Builder::smallTower(rend, position); break;
        case towers::big: *tower = Builder::bigTower(rend, position); break;
        default: return;
    }
    SDL_QueryTexture(tower->tex, NULL, NULL, &tower->getDest()->w, &tower->getDest()->h);
    if(tower->getCost()>coins){
        return;
    }
    coins -= tower->getCost();
    towerList.push_back(*tower);
}

void LevelEngine::engineStep() {
    coinLabel.updateCount(coins);
    coinLabel.render();
    SDL_Event ev;

    for(auto & tower : towerList){
        tower.render();
        Position towerPosition = tower.getPosition();
        if(!tower.canShoot()){
            continue;
        }
        waveEngine.enemyStep(towerPosition, tower);
    }

    for(auto & object: objects){
        object.render();
    }
}

void LevelEngine::generateWave() {
    gameStatus_ = gameStatus::wave;
    waveEngine.getWave();
}

void LevelEngine::defeatScreen() {
    MapObject defeat = MapObject(MAP_WIDTH/3, MAP_HEIGHT/3, rend, IMG_Load("../images/defeat.png"));
    SDL_QueryTexture(defeat.tex, NULL, NULL, &defeat.getDest()->w, &defeat.getDest()->h);
    objects.push_back(defeat);
}

void LevelEngine::victoryScreen() {
    MapObject victory = MapObject(MAP_WIDTH/3, MAP_HEIGHT/3, rend, IMG_Load("../images/victory.png"));
    SDL_QueryTexture(victory.tex, NULL, NULL, &victory.getDest()->w, &victory.getDest()->h);
    objects.push_back(victory);
}



