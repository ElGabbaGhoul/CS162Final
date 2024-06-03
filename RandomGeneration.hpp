//
// Created by Scooter on 5/31/2024.
//

#ifndef CSFINAL_RANDOMGENERATION_HPP
#define CSFINAL_RANDOMGENERATION_HPP

#include <iostream>


const int DUNGEON_SIZE = 16;
const int BOMBS = 4;
const int MONSTERS = 4;
const int GOLD = 4;

void createDungeon(char dungeon[][DUNGEON_SIZE], int bLoc[2], int gLoc[2], int eLoc[2], int mLoc[2], int bombs, int gold, int monsters, char itemChar);
void displayDungeon(char dungeon[][DUNGEON_SIZE]);
std::string getCharName();
std::string generateDungeonName();
void genRandCoords(char dungeon[][DUNGEON_SIZE], int coords[2], char itemChar);
int randRange(int low, int high);


#endif //CSFINAL_RANDOMGENERATION_HPP
