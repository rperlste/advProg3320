#include "Game.h"

bool GameState::visitedRooms[5] = { false, false, false, false, false };

Game::Game(){
    srand( time(NULL) );
    gameState.nextRoom = GameConstants::ROOM_GUARD;
    gameState.adventurer.health = GameConstants::ADV_HEALTH;
    gameState.adventurer.treasure = 0;
}

void Game::run(){
    pressEnterToContinue();
    bool runGame = true;
    printMessage_Title();
    printMessage_Greeting();
    setAdventurerName();
    printMessage_DeathThreat();
    generate_AdventurerWeapon();
    printMessage_EnterTheCastle();
    while( runGame ){
        enterRoom();
        fight();
        runGame = keepPlaying();
        if( runGame ){
            lootRoom();
            selectNextRoom();
        }
        pressEnterToContinue();
    }
    printMessage_EndOfGame();
}


void Game::enterRoom(){
    transitionRoom();
    updateRoomVisitStatus();
    generate_Room();
    printMessage_Room();
}

void Game::generate_Room(){
    generate_Monster();
    generate_Treasure();
}

void Game::transitionRoom(){
    gameState.currentRoom = gameState.nextRoom;
}

void Game::updateRoomVisitStatus(){
    gameState.visitedRooms[gameState.currentRoom.roomId] = true;
}

void Game::generate_Monster(){
    gameState.currentRoom.monster = RandomMonsterFactory::getRandomMonster();
}

void Game::generate_Treasure(){
    gameState.currentRoom.treasure = rand() % GameConstants::TREASURE_VAL + 1;
}

void Game::fight() {
    while( isAlive_Adventurer() && isAlive_Monster() ){
        attack_Adventurer();
        sleepGame( 500 );
        attack_Monster();
        sleepGame( 1000 );
    }
}

bool Game::isAlive_Adventurer(){
    return (gameState.adventurer.health > 0) ? true : false ;
}

bool Game::isAlive_Monster(){
    return (gameState.currentRoom.monster.health > 0) ? true : false ;
}

void Game::attack_Adventurer(){
    int damage = gameState.adventurer.attack();
    gameState.currentRoom.monster.health -= damage;
    printMessage_Combat( gameState.adventurer, 
                         gameState.currentRoom.monster,
                         damage );
}

void Game::attack_Monster(){
    if( isAlive_Monster() ){
        int damage = gameState.currentRoom.monster.attack();
        gameState.adventurer.health -= damage;
        printMessage_Combat( gameState.currentRoom.monster,
                             gameState.adventurer, 
                             damage );
    }
}

bool Game::keepPlaying(){
    if (!isAlive_Adventurer()) {
        return false;
    } else if ( gameState.visitedRooms[0] 
             && gameState.visitedRooms[1] 
             && gameState.visitedRooms[2] 
             && gameState.visitedRooms[3] 
             && gameState.visitedRooms[4] 
             && !isAlive_Monster() ) {
        return false;
    } else {
        return true;
    }
}

void Game::lootRoom(){
    gameState.adventurer.treasure += gameState.currentRoom.treasure;
    printMessage_Treasure( gameState.currentRoom.treasure );
}

void Game::selectNextRoom(){
    if( gameState.currentRoom.roomId < 4 ){
        gameState.nextRoom 
            = GameConstants::ROOM_LIST[ gameState.currentRoom.roomId + 1 ];
    }
}

void Game::sleepGame( unsigned msTime ){
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
        Sleep( msTime );
    #else
        sleep( 1000 * msTime );
    #endif
}

void Game::printMessage_Greeting() {
    std::cout 
        << "...\"Welcome to the Console Castle of DOOM!\"..."
        << "\n\n...\"All ye who (press) ENTER will die by the hand of "
        << "my minions!\"...";
}

void Game::printMessage_EndOfGame(){
    if( gameState.adventurer.health > 0 ){
        std::cout << "\nYou have defeated the Console Castle of Doom's"
            << " many horrific inhabitants,\nand walked away with "
            << gameState.adventurer.treasure << " treasure. You might"
            << " want a bandaid though,\nbecause you only have "
            << gameState.adventurer.health << " health remaining."
            << "\n\nYOU WIN!!!\n\n";
    } else {
        std::cout << "\n...\"You fool! I warned you of the dangers, and now you"
            << "\nlie in a pool of your own blood!\"..."
            << "\n\nYOU LOSE!!!\n\n";
    }
}

void Game::printMessage_Room(){
    std::cout << "\n" << gameState.adventurer.name << " has entered the " 
        << gameState.currentRoom.name << ".\n";
}

void Game::printMessage_Combat( const Actor& actor1, 
                                const Actor& actor2, 
                                int damage ){
    std::cout << "\n" << actor1.name << " swings his " 
        << actor1.weapon.name << " at " << actor2.name;
    if( damage == 0 ){
        std::cout << " and misses!";
    } else {
        std::cout << " and hits for " << damage << " damage.";
    }
}

void Game::printMessage_Treasure( unsigned treasure ){
    std::cout << "\n" << gameState.adventurer.name << " has found " 
        << treasure << " treasure!";
}

void Game::printMessage_Weapon( const Weapon& weapon ){
    std::cout << "\n\nYou have found a " << weapon.name << "!"
        << "\nWield it wisely and with tact, or die by your own hand.";
}

void Game::setAdventurerName(){
    gameState.adventurer.name = "";
    while( gameState.adventurer.name == "" ){
        std::cout << "\n...\"What is the name of the fool who enters "
            << "my grounds?\"..."
            << "\n\nEnter your name: ";
        std::getline( std::cin, gameState.adventurer.name );
    }
}

void Game::printMessage_DeathThreat(){
    std::cout << "\n...\"Turn away now, and I will spare your measly life "
        << gameState.adventurer.name << "!\"...";
    sleepGame( 1000 );
}

void Game::pressEnterToContinue(){
    std::cout << std::string( "\n" );
    std::cout << "Press ENTER to continue... ";
    std::cin.ignore( INT_MAX, '\n' );
}

void Game::generate_AdventurerWeapon(){
    gameState.adventurer.weapon = GameConstants::ADV_WEP_LIST[ rand() % 3 ];
}

void Game::printMessage_Title(){
    std::cout << "\n\n" << std::string( 79, '-' ) << "\n"
    << " _____                       _           \n"
    << "/  __ \\                     | |          \n"
    << "| /  \\/ ___  _ __  ___  ___ | | ___      \n"
    << "| |    / _ \\| '_ \\/ __|/ _ \\| |/ _ \\     \n"
    << "| \\__/\\ (_) | | | \\__ \\ (_) | |  __/     \n"
    << " \\____/\\___/|_| |_|___/\\___/|_|\\___|        \n"                                                                
    << " _____           _   _               __  \n"
    << "/  __ \\         | | | |             / _| \n"
    << "| /  \\/ __ _ ___| |_| | ___    ___ | |_  \n"
    << "| |    / _` / __| __| |/ _ \\  / _ \\|  _| \n"
    << "| \\__/\\ (_| \\__ \\ |_| |  __/ | (_) | |   \n"
    << " \\____/\\__,_|___/\\__|_|\\___|  \\___/|_|   \n"                                   
    << " ______ _____ ________  ___  _          \n" 
    << "|  _  \\  _  ||  _  |  \\/  | | |          \n"
    << "| | | | | | || | | | .  . | | |          \n"
    << "| | | | | | || | | | |\\/| | | |          \n"
    << "| |/ /\\ \\_/ /\\ \\_/ / |  | | |_|          \n"
    << "|___/  \\___/  \\___/\\_|  |_/ (_)          \n\n";
                                         
}

void Game::printMessage_EnterTheCastle(){
    std::cout << "\n\nIgnoring the mysterious calls to turn back, our great"
        << " hero " << gameState.adventurer.name 
        << "\npushes the heavy castle doors open, and hears a loud crash.";
    sleepGame( 3000 );
    std::cout << "\n\nA skelton had fallen out from between the doors."
        << "\nSomething shiny lay within its ribcage.";
    sleepGame( 3000 );
    printMessage_Weapon( gameState.adventurer.weapon );
    sleepGame(5000);
    std::cout << "\n\n" << gameState.adventurer.name 
        << " lets out a deep breath and enters the Castle...\n";
    pressEnterToContinue();
}