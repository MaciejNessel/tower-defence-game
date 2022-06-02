//
// Created by Maciej on 26.05.2022.
//

#include "../headers/Engine.h"

void Engine::waveStep() {

    for(int i=0; i<enemyList.size(); i++){
        enemyList[i].rendBullets();
        Position position = enemyList[i].getCenterPosition();
        if(enemyList[i].hp<=0){
            enemyList.erase(enemyList.begin()+i);
            continue;
        }
        bool isEnd = map.isEnd(position);
        if(isEnd){
            std::cout<<"DEFEAT"<<std::endl;
            isRunning = false;
        }
        Directions nextStep = findNextStep(enemyList[i]);
        enemyList[i].move(nextStep);
        enemyList[i].render();
    }
}

void Engine::addEnemyFromWave() {
    addEnemy(Position(25, 25));
    noEnemies--;
}

void Engine::start() {

    isRunning = true;
    int timer = 0;

    while (isRunning){
        timer ++;
        SDL_Event event;
        GameBarObject *result = nullptr;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: isRunning = false; break;
                case SDL_MOUSEBUTTONDOWN: result = gameBar.click(event); break;
            }
            if(result != nullptr){
                Position towerPosition = map.generateTowerPosition(Position(event.button.x, event.button.y));
//                Position towerPosition = (Position(event.button.x, event.button.y));
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

        gameBar.render();
        this->engineStep();

        waveStep();
        if(noEnemies>0 && timer % 100 == 0){
            addEnemyFromWave();
        }

        SDL_RenderPresent(rend);

        SDL_Delay(1000 / 60);
    }
}

void Engine::addEnemy(Position position) {
    Enemy en = Enemy(rend, position.x(), position.y());
    SDL_QueryTexture(en.tex, NULL, NULL, &en.getDest()->w, &en.getDest()->h);
    enemyList.push_back(en);
}

void Engine::addTower(Position position, enum towers type) {
    Tower *tower = (Tower*) calloc(sizeof (Tower), 1);
    switch (type) {
        case towers::small: *tower = Builder::smallTower(rend, position); break;
        case towers::big: *tower = Builder::bigTower(rend, position); break;
        default: return;
    }
    SDL_QueryTexture(tower->tex, NULL, NULL, &tower->getDest()->w, &tower->getDest()->h);
    towerList.push_back(*tower);
}

void Engine::engineStep() {
    SDL_Event ev;

    for(auto & tower : towerList){
        tower.render();
        Position towerPosition = tower.getPosition();
        if(!tower.canShoot){
            continue;
        }
        for(int i=0; i<enemyList.size(); i++){
            Position enemyPosition = enemyList[i].getPosition();
            bool shoot = enemyPosition.isTargetCircle(towerPosition, tower.getRange());
            if(shoot && enemyList[i].virtualHp>0){
                enum bullets bulletType = tower.getBulletType();
                enemyList[i].addBullet(Position(towerPosition.x()+tower.getDest()->w*0.25, towerPosition.y()), bulletType);
                enemyList[i].dealVirtualDamage(tower.getForceAndShoot());
                break;
            }
        }
    }
}

Directions Engine::findNextStep(Enemy enemy) {
    Position actualPosition = enemy.getCenterPosition();
    int blockX = actualPosition.x() / BLOCK_BACKGROUND_SIZE;
    int blockY = actualPosition.y() / BLOCK_BACKGROUND_SIZE;
    Directions dir = map.nextEnemyStep(Position(blockX, blockY));
    return dir;

}

void Engine::generateWave() {
    noEnemies = 10;
}
