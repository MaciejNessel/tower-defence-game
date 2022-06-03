//
// Created by Maciej on 02.06.2022.
//

#include "../headers/WaveEngine.h"

std::vector<std::string> WaveEngine::splitBySpace(std::string line) {
    std::string space_delimiter = " ";
    std::vector<std::string> words{};
    size_t pos = 0;
    size_t lastPos = 0;
    while ((pos = line.find(space_delimiter)) != std::string::npos) {
        words.push_back(line.substr(0, pos));
        line.erase(0, pos + space_delimiter.length());
        lastPos = pos;
    }
    words.push_back(line.substr(fmax(0, lastPos-2), line.size()));
    return words;
}

void WaveEngine::loadLevel() {
    std::ifstream myfile (levelWaveName);
    std::string line;
    if (myfile.is_open())
    {
        while ( std::getline (myfile, line) )
        {
            std::vector<std::string> words = splitBySpace(line);
            if(words.size()<3){
                break;
            }
            waves.push_back(Wave(std::stoi(words.at(0)), std::stoi(words.at(1)), std::stoi(words.at(2))));
        }
        myfile.close();
    }
    myfile.close();

}

void WaveEngine::getWave() {
    if(noEnemies>0 || enemyList.size() > 0){
        return;
    }
    if(currentWave<waves.size()){
        Wave w = waves.at(currentWave);
        currentWave++;
        noEnemies = w.enemies;
    }
}

void WaveEngine::addEnemy(Position position) {
    Enemy en = Enemy(rend, position.x(), position.y());
    SDL_QueryTexture(en.tex, NULL, NULL, &en.getDest()->w, &en.getDest()->h);
    enemyList.push_back(en);
}

Directions WaveEngine::findNextStep(Enemy enemy, Map map) {
    Position actualPosition = enemy.getCenterPosition();
    int blockX = actualPosition.x() / BLOCK_BACKGROUND_SIZE;
    int blockY = actualPosition.y() / BLOCK_BACKGROUND_SIZE;
    Directions dir = map.nextEnemyStep(Position(blockX, blockY));
    return dir;
}

enum gameStatus WaveEngine::waveStep(Map map, int* coins) {

    timer++;
    if(noEnemies>0 && timer % 100 == 0){
        addEnemyFromWave();
    }

    for(int i=0; i<enemyList.size(); i++){
        enemyList[i].rendBullets();
        Position position = enemyList[i].getCenterPosition();
        if(enemyList[i].hp<=0){
            *coins += ENEMY_FIRST_HP / 5;
            enemyList.erase(enemyList.begin()+i);
            continue;
        }
        bool isEnd = map.isEnd(position);
        if(isEnd){
            return gameStatus::defeat;
        }
        Directions nextStep = findNextStep(enemyList[i], map);
        enemyList[i].move(nextStep);
        enemyList[i].render();
    }
}

int WaveEngine::enemyStep(Position towerPosition, Tower tower) {
    for(int i=0; i<enemyList.size(); i++){
        Position enemyPosition = enemyList[i].getPosition();
        bool shoot = enemyPosition.isTargetCircle(towerPosition, tower.getRange());
        if(shoot && enemyList[i].virtualHp>0){
            enum bullets bulletType = tower.getBulletType();
            enemyList[i].addBullet(Position(towerPosition.x()+tower.getDest()->w*0.25, towerPosition.y()), bulletType);
            enemyList[i].dealVirtualDamage(tower.getForceAndShoot());
        }
    }
    return 0;
}

void WaveEngine::addEnemyFromWave() {
    addEnemy(startPosition);
    noEnemies--;
}

void WaveEngine::destroy() {
    waves.clear();
    for(int i=0; i<enemyList.size(); i++){
        enemyList.at(i).destroy();
    }
}
