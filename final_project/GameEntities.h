#ifndef _GAME_ENTITIES_H
#define _GAME_ENTITIES_H

#include <string>
#include <cstdlib>
#include <utility>


class GameEntity {
public:
    std::string name;
};

class Weapon : public GameEntity {
public:
    Weapon(){}
    Weapon( const std::string& name, 
            const int damage,
            const int accuracy );

    // Data members
    int damage;
    int accuracy;
};

class Actor : public GameEntity {
public:
    Actor(){}
    Actor(  const std::string& name, 
            const int health,
            const Weapon& weapon );
    int attack();

    // Data members
    int health;
    Weapon weapon;
};

class Adventurer : public Actor {
public:
    Adventurer(){}
    Adventurer( const std::string& name, 
                const int health,
                const Weapon& weapon,
                const int treasure = 0 );

    // Data members
    int treasure;
};

class Room : public GameEntity {
public:
    Room(){}
    Room( const std::string& name,
          const int roomId );

    // Data members
    int treasure;
    int roomId;
    Actor monster;
};




#endif