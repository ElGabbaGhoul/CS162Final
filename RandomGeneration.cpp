//
// Created by Scooter on 5/31/2024.
//


#include "MonsterClass.hpp"
#include "RandomGeneration.hpp"
#include <random>
#include <iostream>
#include <thread>
#include <chrono>




void createDungeon(char dungeon[][DUNGEON_SIZE], int bLoc[2], int gLoc[2], int eLoc[2], int mLoc[2], int bombs, int gold, char itemChar, Monster* monsters[MONSTER_COUNT], std::string playerName){
    for (int i = 0; i < DUNGEON_SIZE; i++){
        for (int j = 0; j < DUNGEON_SIZE; j++){
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
        monsters[i]->setDungeonX(mLoc[0]);
        monsters[i]->setDungeonY(mLoc[1]);
    }
// Place Gold
    for (int i = 0; i < gold; i++){
        genRandCoords(dungeon, gLoc, 'G');
    }
// Place Exit
    genRandCoords(dungeon, eLoc, 'E');

    std::string dungeonName = generateDungeonName();
    displayInstructions(playerName);
    std::cout << "Dungeon Created! Now prepare yourself to face..." << std::endl;
    twoSecPause();
    std::cout << dungeonName << std::endl;
}

void createNextDungeon(char dungeon[][DUNGEON_SIZE], int bLoc[2], int gLoc[2], int eLoc[2], int mLoc[2], int bombs, int gold, char itemChar, Monster* monsters[MONSTER_COUNT]) {
    for (int i = 0; i < DUNGEON_SIZE; i++){
        for (int j = 0; j < DUNGEON_SIZE; j++){
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
        monsters[i]->setDungeonX(mLoc[0]);
        monsters[i]->setDungeonY(mLoc[1]);
    }
// Place Gold
    for (int i = 0; i < gold; i++){
        genRandCoords(dungeon, gLoc, 'G');
    }
// Place Exit
    genRandCoords(dungeon, eLoc, 'E');

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

    while (!validIn) {
        std::cout << "Greetings traveler, what is your name?" << std::endl;
        std::cin >> player;

        if (!player.empty()){
            if (!isAllChars(player)){
                std::cin.clear();
                std::cin.ignore(50000, '\n');
                std::cerr << "Error: No special characters in your name please."<< std::endl;
                std::cerr << "Your first name should be Alpha only (A-Z, a-z)." << std::endl;
            } else {
                for (char &c: player){
                    c = std::tolower(static_cast<unsigned char>(c));
                }
                player[0] = std::toupper(static_cast<unsigned char>(player[0]));
                validIn = true;
            }
        }
    }
    return player;
}

bool isAllChars(const std::string &str) {
    for (char c : str) {
        if (!std::isalpha(c)) {
            return false;
        }
    }
    return true;
}

void displayInstructions(std::string& playerName){
    std::cout << "Press ESC at any time to close the game!\n" << std::endl;
    oneSecPause();
    std::cout << "Use WASD to walk around the dungeon!\n" << std::endl;
    oneSecPause();
    std::cout << "Collect gold! Avoid bombs! Kill monsters!\n" << std::endl;
    oneSecPause();
    std::cout << "Navigate to the exit!\n" << std::endl;
    oneSecPause();
    std::cout << "Purchase upgrades on sanctuary levels! (Coming Soon!)\n" << std::endl;
    oneSecPause();
    std::cout << "How far can YOU go, "<< playerName << "!?\n" << std::endl;
    oneSecPause();
}

std::string generateDungeonName() {
    std::string dungeonName;

    std::string prefixes[] = {"Forsaken", "Abandoned", "Cursed"};

    std::string nouns[] = {"Cavern", "Mine", "Swamp"};

    std::string suffixes[] = {"Crazed", "Vicious", "Malevolent"};

    std::string enemies[] = {"Cadavers", "Spirits", "Slimes"};

    dungeonName = "The " + prefixes[randRange(0,2)] + " " + nouns[randRange(0,2)] + " of " + suffixes[randRange(0,2)] + " " + enemies[randRange(0,2)] + "!\n" ;

    return dungeonName;
}

void genRandCoords(char dungeon[][DUNGEON_SIZE], int coords[2], char itemChar) {
    int x, y;

    do {
        x = randRange(1, DUNGEON_SIZE - 1);
        y = randRange(1, DUNGEON_SIZE - 1);
    } while (dungeon[y][x] != '_' && (x != 1 && y != 1));

        dungeon[y][x] = itemChar;
        coords[0] = x;
        coords[1] = y;
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