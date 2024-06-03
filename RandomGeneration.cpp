//
// Created by Scooter on 5/31/2024.
//

#include "RandomGeneration.hpp"
#include <random>
#include <iostream>

void createDungeon(char dungeon[][DUNGEON_SIZE], int bLoc[2], int gLoc[2], int eLoc[2], int mLoc[2], int bombs, int gold, int monsters, char itemChar){
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
    for (int i = 0; i < monsters; i++){
        genRandCoords(dungeon, mLoc, 'M');
    }
// Place Gold
    for (int i = 0; i < gold; i++){
        genRandCoords(dungeon, gLoc, 'G');
    }
// Place Exit
    genRandCoords(dungeon, eLoc, 'E');
    std::string dungeonName = generateDungeonName();
    std::cout << "Dungeon Created! Now prepare yourself to face..." << std::endl;
    std::cout << dungeonName << std::endl;
}

void displayDungeon(char dungeon[][DUNGEON_SIZE]){
    for (int i = 0; i < DUNGEON_SIZE; i++) {
        for (int j = 0; j < DUNGEON_SIZE; j++) {
            printf("%c", dungeon[i][j]);
        }
        printf("\n");
    }
//    for (int i = DUNGEON_SIZE - 1; i >= 0; i--) {
//        for (int j = DUNGEON_SIZE - 1; j >= 0; j--) {
//            printf("%c", dungeon[i][j]);
//        }
//        printf("\n");
//    }
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

//void displayInstructions(const std::string& charName, const std::string& ){
//    std::cout << ""
//}

std::string generateDungeonName() {
    std::string dungeonName;

    std::string prefixes[] = {"Howling", "Abandoned", "Damned"};

    std::string nouns[] = {"Cavern", "Field", "Swamp"};

    std::string suffixes[] = {"Crazed", "Undead", "Bloodthirsty"};

    std::string enemies[] = {"Cadavers", "Spirits", "Penguins"};

    dungeonName = prefixes[randRange(0,2)] + " " + nouns[randRange(0,2)] + " of the " + suffixes[randRange(0,2)] + " " + enemies[randRange(0,2)] + "!" ;

    return dungeonName;
}

void genRandCoords(char dungeon[][DUNGEON_SIZE], int coords[2], char itemChar) {
    int x, y;
    do {
        x = randRange(0, DUNGEON_SIZE - 1);
        y = randRange(0, DUNGEON_SIZE - 1);
    } while (dungeon[x][y] != '_');

    dungeon[x][y] = itemChar;
    coords[0] = x;
    coords[1] = y;
}

int randRange(int low, int high){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(low, high);
    return dis(gen);
}