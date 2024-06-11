//
// Created by Scooter on 5/31/2024.
//

#include "RandomGeneration.hpp"
#include "MonsterClass.hpp"
#include <random>
#include <iostream>
#include <thread>
#include <chrono>


Monster* monsters[MONSTER_COUNT];


void createDungeon(char dungeon[][DUNGEON_SIZE], int bLoc[2], int gLoc[2], int eLoc[2], int mLoc[2], int pLoc[2], int pLocNew[2], int bombs, int gold, int monstersCount, char itemChar){
    for (int i = 0; i < DUNGEON_SIZE; i++){
        for ( int j = 0; j < DUNGEON_SIZE; j++){
            if (i == 0 || i == DUNGEON_SIZE - 1 || j == 0 || j == DUNGEON_SIZE - 1) {
                dungeon[i][j] = '#';
            } else {
                dungeon[i][j] = itemChar;
            }
        }
    }

// Place Bombs
    for (int i = 0; i < bombs; i++){
        genRandCoords(dungeon, bLoc, 'B');
    }
// Place Monsters
    for (int i = 0; i < MONSTER_COUNT; i++){

        int monsterType = randRange(0,2);
        if (monsterType == 0){
            monsters[i] = new Skelly();
        } else if (monsterType == 1){
            monsters[i] = new Slime();
        } else {
            monsters[i] = new Ghost();
        }

        genRandCoords(dungeon, mLoc, monsters[i]->getLetter());


        std::cout << monsters[i]->getType() << std::endl;

    }
// Place Gold
    for (int i = 0; i < gold; i++){
        genRandCoords(dungeon, gLoc, 'G');
    }
// Place Exit
    genRandCoords(dungeon, eLoc, 'E');

    std::string dungeonName = generateDungeonName();
    displayInstructions();
    std::cout << "Dungeon Created! Now prepare yourself to face..." << std::endl;
    twoSecPause();
    std::cout << dungeonName << std::endl;
}

void resolveCombat(char dungeon[][DUNGEON_SIZE]){
    // get dungeon tile
    // get monster from dungeon tile
    // playercurrent = current - monster attack / player armor
    // monstercurrent = current - player attack / player armor
    // update accordingly

}

void displayDungeon(char dungeon[][DUNGEON_SIZE]){
    for (int i = 0; i < DUNGEON_SIZE; i++) {
        for (int j = 0; j < DUNGEON_SIZE; j++) {
            printf("%c", dungeon[i][j]);
        }
        printf("\n");
    }
}

std::string getCharName() {
    std::string player;
    bool validIn = false;
    std::cout << "Greetings traveler, what is your name?" << std::endl;
    std::cin >> player;

    while (!validIn) {
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(40000, '\n');
            std::cout << "Please enter a name with at least 3 characters." << std::endl;
        } else {
            validIn = true;
        }
    }
    return player;
}

void displayInstructions(){
    std::cout << "Press ESC at any time to close the game!\n" << std::endl;
    oneSecPause();
    std::cout << "Use WASD to walk around the dungeon!\n" << std::endl;
    oneSecPause();
    std::cout << "Collect gold! Avoid bombs! Kill monsters!\n" << std::endl;
    oneSecPause();
    std::cout << "Navigate to the exit!\n" << std::endl;
    oneSecPause();
    std::cout << "Purchase upgrades on sanctuary levels!\n" << std::endl;
    oneSecPause();
}

std::string generateDungeonName() {
    std::string dungeonName;

    std::string prefixes[] = {"Howling", "Abandoned", "Damned"};

    std::string nouns[] = {"Cavern", "Mine", "Swamp"};

    std::string suffixes[] = {"Crazed", "Vicious", "Bloodthirsty"};

    std::string enemies[] = {"Cadavers", "Spirits", "Slimes"};

    dungeonName = prefixes[randRange(0,2)] + " " + nouns[randRange(0,2)] + " of the " + suffixes[randRange(0,2)] + " " + enemies[randRange(0,2)] + "!\n" ;

    return dungeonName;
}

void genRandCoords(char dungeon[][DUNGEON_SIZE], int coords[2], char itemChar) {
    int x, y;

    do {
        x = randRange(1, DUNGEON_SIZE - 1);
        y = randRange(1, DUNGEON_SIZE - 1);
    } while (dungeon[x][y] != '_');

        dungeon[x][y] = itemChar;
        coords[0] = x;
        coords[1] = y;
        std::cout << itemChar << " tiles: " << coords[1] << ", " << coords[0] << std::endl;
}

int randRange(int low, int high){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(low, high);
    return dis(gen);
}

void twoSecPause(){
    std::this_thread::sleep_for(std::chrono::milliseconds(2000));
}

void oneSecPause(){
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}