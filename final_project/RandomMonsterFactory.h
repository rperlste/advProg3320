#ifndef _RANDOM_MONSTER_FACTORY_
#define _RANDOM_MONSTER_FACTORY_

#include "GameConstants.h"
#include <cstdlib>
#include <time.h>

class RandomMonsterFactory {
public:
    static Actor getRandomMonster();
private:
    static void createMonster( Actor& );
    static void createWeapon( Actor& );
};

#endif