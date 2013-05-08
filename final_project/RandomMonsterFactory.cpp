#include "RandomMonsterFactory.h"


Actor RandomMonsterFactory::getRandomMonster(){
    Actor monster;
    createMonster( monster );
    createWeapon( monster );
    return monster;
}

void RandomMonsterFactory::createMonster( Actor& monster ){
    srand( time(NULL) );
    GameConstants::geMonPair monsterType = GameConstants::MON_LIST[rand() % 3];
    monster.name = monsterType.first;
    monster.health = monsterType.second;
}

void RandomMonsterFactory::createWeapon( Actor& monster ){
    srand( time(NULL) );
    monster.weapon = GameConstants::MON_WEP_LIST[rand() % 3];
}