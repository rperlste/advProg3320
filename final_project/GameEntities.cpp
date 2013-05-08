#include "GameEntities.h"

Weapon::Weapon( const std::string& name, 
                const int damage,
                const int accuracy ){
    this->name = name;
    this->damage = damage;
    this->accuracy = accuracy;
}

Actor::Actor( const std::string& name, 
              const int health,
              const Weapon& weapon ){
    this->name = name;
    this->health = health;
    this->weapon = weapon;
}

int Actor::attack(){
    if ((rand() % 100) < weapon.accuracy ) {
        return weapon.damage;
    } else {
        return 0;
    }
}

Adventurer::Adventurer( const std::string& name, 
                        const int health,
                        const Weapon& weapon,
                        const int treasure ){
    this->name = name;
    this->health = health;
    this->weapon = weapon;
    this->treasure = treasure;
}

Room::Room( const std::string& name,
            const int roomId ){
    this->name = name;
    this->roomId = roomId;
}
