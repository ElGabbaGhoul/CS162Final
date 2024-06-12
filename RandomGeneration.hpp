//
// Created by Scooter on 5/31/2024.
//

#ifndef CSFINAL_RANDOMGENERATION_HPP
#define CSFINAL_RANDOMGENERATION_HPP

#include <iostream>

#include "MonsterClass.hpp"

const int DUNGEON_SIZE = 16;
const int MONSTER_COUNT = 4;
const int BOMBS = 4;
const int GOLD = 4;

class Monster;


void createDungeon(char dungeon[][DUNGEON_SIZE], int bLoc[2], int gLoc[2], int eLoc[2], int mLoc[2], int bombs, int gold, char itemChar, Monster* monsArr[]);
void displayDungeon(char dungeon[][DUNGEON_SIZE]);
std::string getCharName();
std::string generateDungeonName();
void displayInstructions();
void genRandCoords(char dungeon[][DUNGEON_SIZE], int coords[2], char itemChar);
int randRange(int low, int high);
void twoSecPause();
void oneSecPause();


#endif //CSFINAL_RANDOMGENERATION_HPP
