#ifndef _GAME_H
#define _GAME_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include <windows.h>
#else 
#include <unistd.h>
#endif


#include <iostream>
#include <cstdlib>
#include "GameState.h"
#include "GameConstants.h"
#include "RandomMonsterFactory.h"

    struct GameState {
        static bool visitedRooms[5];
        Room currentRoom;
        Room nextRoom;
        Adventurer adventurer;
    };

class Game { 
public:
    Game();
    void run();
private:
    // Messages
    void printMessage_Greeting();
    void printMessage_EndOfGame();
    void printMessage_Room();
    void printMessage_Combat( const Actor&, const Actor&, int );
    void printMessage_Treasure( unsigned );
    void printMessage_Weapon( const Weapon& );
    void printMessage_DeathThreat();
    void printMessage_Title();
    void printMessage_EnterTheCastle();


    // Room
    void generate_Room();
    void generate_Treasure();
    void enterRoom();
    void selectNextRoom();
    void lootRoom();
    void transitionRoom();
    void updateRoomVisitStatus();

    // Actors
    void setAdventurerName();
    void generate_AdventurerWeapon();
    void generate_Monster();
    inline bool isAlive_Adventurer();
    inline bool isAlive_Monster();
    void fight();
    void attack_Adventurer();
    void attack_Monster();

    // Game
    void init();
    bool keepPlaying();
    void sleepGame( unsigned );
    void pressEnterToContinue();

    // Persistent data member
    GameState gameState;
};

#endif