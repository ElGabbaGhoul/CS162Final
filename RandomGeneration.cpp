//
// Created by Scooter on 5/31/2024.
//

#include "RandomGeneration.hpp"
#include <cstdlib>
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

    std::cout << "Dungeon Created! Now prepare yourself to face..." << std::endl;
    displayDungeonName();
}

void displayDungeon(char dungeon[][DUNGEON_SIZE]){
    for (int y = 0; y < DUNGEON_SIZE; y++){
        for (int x = 0; x < DUNGEON_SIZE; x++){
            std::cout << dungeon[x][y];
        }
        std::cout << std::endl;
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
            std::cout << "Greetings, " << player << "." << std::endl;
            validIn = true;
        }
    }
    return player;
}
void displayDungeonName() {

    std::string prefixes[] = {"Howling", "Abandoned", "Damned"};

    std::string nouns[] = {"Cavern", "Field", "Swamp"};

    std::string suffixes[] = {"Crazed", "Undead", "Bloodthirsty"};

    std::string enemies[] = {"Cadavers", "Spirits", "Penguins"};

    std::cout << prefixes[randRange(0,2)] << " " << nouns[randRange(0,2)]
              << " of the " << suffixes[randRange(0,2)] << " " << enemies[randRange(0,2)] << "!"
              << std::endl;
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

int randRange(int low, int high) {
    return rand() % (high - low + 1) + low;
}

