#ifndef _GAME_CONSTANTS_
#define _GAME_CONSTANTS_

#include "GameEntities.h"

namespace GameConstants {

    // Rooms
    const Room ROOM_GUARD   ( "Guard Room", 0 );
    const Room ROOM_COURT   ( "Courtyard", 1 );
    const Room ROOM_ART     ( "Art Room", 2 );
    const Room ROOM_HALL    ( "Great Hall", 3 );
    const Room ROOM_DUNGEON ( "Dungeon", 4 );
    const Room ROOM_LIST[5] = { ROOM_GUARD,
                                ROOM_COURT,
                                ROOM_ART,
                                ROOM_HALL,
                                ROOM_DUNGEON };

    const unsigned ROOM_ADJ_MATRIX[5][5] = {
        {0,  1,  0,  0,  0},
        {1,  0,  1,  1,  0},
        {0,  1,  0,  0,  0},
        {0,  1,  0,  0,  1},
        {0,  0,  0,  1,  0}
    };

    // ADVENTURER
    const unsigned ADV_HEALTH = 50;
    const unsigned TREASURE_VAL = 100;

    // Adventurer Weapons
    const Weapon WEP_SWORD	( "Sword",  5,  40 );
    const Weapon WEP_AXE    ( "Axe",    4,	50 );
    const Weapon WEP_SPEAR	( "Spear",	3,	60 );
    const Weapon ADV_WEP_LIST[3] = { WEP_SWORD,	WEP_AXE, WEP_SPEAR };

    // Monsters
    typedef std::pair<std::string,unsigned> geMonPair;
    const geMonPair MON_TROLL	( "Troll",		13 );
    const geMonPair MON_GELFING ( "Gelfing",	6 );
    const geMonPair MON_BELF	( "Belf",		7 );
    const geMonPair MON_LIST[3] = { MON_TROLL, MON_GELFING, MON_BELF };

    // Monster weapons
    const Weapon WEP_TROTH	( "Troth",	5,	50 );
    const Weapon WEP_GEFF	( "Geff",   4,  20 );
    const Weapon WEP_BEFF	( "Beff",   3,  35 );
    const Weapon MON_WEP_LIST[3] = { WEP_TROTH,	WEP_GEFF, WEP_BEFF };
}

#endif