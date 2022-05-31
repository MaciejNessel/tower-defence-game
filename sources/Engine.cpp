//
// Created by Maciej on 26.05.2022.
//
#include "../headers/Engine.h"

void Engine::start() {
    addEnemy(Position(25, 25));
    addTower(Position(200, 30));
    addTower(Position(260, 256));
    isRunning = true;
    int cnt = 0;
    while (isRunning){
        cnt ++;
        SDL_Event event;
        MapObject *result = nullptr;
        bool isSelected;
        Position selectedField = Position(-100, -100);
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: isRunning = false; break;
                case SDL_MOUSEBUTTONDOWN: result = gameBar.click(event); break;
                default:
                    isSelected = gameBar.isSelected();
                    if(isSelected){
                        selectedField = Position(event.button.x, event.button.y);
                    }
                    break;
            }
            if(result != nullptr){
                addTower(Position(event.button.x, event.button.y));
            }

        }

        SDL_RenderClear(rend);
        map.mapRender(selectedField);

        if(cnt%100==0){
            cnt = 0;
            addEnemy(Position(25, 25));
        }

        this->engineStep();

        SDL_RenderPresent(rend);

        SDL_Delay(1000 / 60);
    }
}

void Engine::addEnemy(Position position) {
    Enemy en = Enemy(rend, position.x(), position.y());
    SDL_QueryTexture(en.tex, NULL, NULL, &en.getDest()->w, &en.getDest()->h);
    enemyList.push_back(en);
}

void Engine::addTower(Position position) {
    Tower tower = Tower(rend, position.x(), position.y());
    SDL_QueryTexture(tower.tex, NULL, NULL, &tower.getDest()->w, &tower.getDest()->h);
    towerList.push_back(tower);
}

void Engine::engineStep() {
    gameBar.render();
    SDL_Event ev;

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
                enemyList[i].addBullet(Position(towerPosition.x()+tower.getDest()->w*0.25, towerPosition.y()));
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
