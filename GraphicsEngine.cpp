//
// Created by Scooter on 6/2/2024.
//

#include "GraphicsEngine.hpp"
#include "MonsterClass.hpp"
#include "RandomGeneration.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>

using namespace std;

int nScreenWidth = 120;
int nScreenHeight = 40;

float fPlayerX = 1.0f;
float fPlayerY = 1.0f;
float fPlayerA = 0.0f;

int nMapHeight = 16;
int nMapWidth = 16;

float fFOV = 3.14159f / 4.0f;
float fDepth = 16.0f;

int bLoc2[2], gLoc2[2], eLoc2[2], mLoc2[2];
char itemChar2 = '_';

void InitializeFPS() {
    if (!GetConsoleWindow()) {
        AllocConsole();
    }

    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
    if (hConsole == INVALID_HANDLE_VALUE) {
        cout << "Failed to create console screen buffer" << endl;
        exit(1);
    }
    SetConsoleActiveScreenBuffer(hConsole);
    ShowWindow(GetConsoleWindow(), SW_SHOW);
}

// Controls
void UpdatePlayer(float fElapsedTime, const char dungeon[][16]) {
    if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
        float newX = fPlayerX + sinf(fPlayerA) * 2.5f * fElapsedTime;
        float newY = fPlayerY + cosf(fPlayerA) * 2.5f * fElapsedTime;
        if (dungeon[(int)newY][(int)newX] != '#' && newX >= 0 && newX < nMapWidth && newY >= 0 && newY < nMapHeight) {
            fPlayerX = newX;
            fPlayerY = newY;
        }
    }

    if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
        float newX = fPlayerX - sinf(fPlayerA) * 4.0f * fElapsedTime;
        float newY = fPlayerY - cosf(fPlayerA) * 4.0f * fElapsedTime;
        if (dungeon[(int)newY][(int)newX] != '#' && newX >= 0 && newX < nMapWidth && newY >= 0 && newY < nMapHeight) {
            fPlayerX = newX;
            fPlayerY = newY;
        }
    }

    if (GetAsyncKeyState((unsigned short)'A') & 0x8000) {
        fPlayerA -= (1.0f) * fElapsedTime;
    }

    if (GetAsyncKeyState((unsigned short)'D') & 0x8000) {
        fPlayerA += (1.0f) * fElapsedTime;
    }
}

void checkTile(char dungeon[][DUNGEON_SIZE], Player* player, Monster* monsters[MONSTER_COUNT]) {
    int x = (int)fPlayerY;
    int y = (int)fPlayerX;
    int armor = player->getArmor();
    int currentHealth = player->getCurrentHealth();

// AAAAAAAAAA I FIGURED IT OUT
    for (int i = 0; i < MONSTER_COUNT; ++i) {
        int monsterX = monsters[i]->getDungeonX();
        int monsterY = monsters[i]->getDungeonY();


    if (dungeon[x][y] == 'B') {
        player->setCurrentHealth(player->getCurrentHealth() - 1);
        dungeon[x][y] = '_';
    } else if (dungeon[x][y] == 'G') {
        player->setGold(player->getGold() + 5);
        dungeon[x][y] = '_';
    } else if (dungeon[x][y] == 'O' ||dungeon[x][y] == 'L' ||dungeon[x][y] == 'S'){
        bool wasHit = false;
        while (!wasHit && (x >= monsterX && y < monsterY)){
            int dented = armor - 1;
            wasHit = true;
            player->setArmor(dented);
            if (armor == 0 && currentHealth > 0){
                int whacked = currentHealth - 1;
                player->setCurrentHealth(whacked);
            }
            dungeon[x][y] = '_';
        }
    } else if (dungeon[x][y] == 'E'){
        createNextDungeon(dungeon, bLoc2, gLoc2, eLoc2, mLoc2, BOMBS, GOLD, itemChar2, monsters);
    }
    }
}

void RenderFrame(wchar_t* screen, const char dungeon[][16], HANDLE hConsole, DWORD& dwBytesWritten, float fElapsedTime, Player* player) {
    for (int x = 0; x < nScreenWidth; x++) {
        float fRayAngle = (fPlayerA - fFOV / 2.0f) + ((float)x / (float)nScreenWidth) * fFOV;
        float fDistanceToWall = 0;
        bool bHitWall = false;
        bool bBoundary = false;
        float fEyeX = sinf(fRayAngle);
        float fEyeY = cosf(fRayAngle);
        while (!bHitWall && fDistanceToWall < fDepth) {
            fDistanceToWall += 0.1f;
            int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
            int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);
            if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight) {
                bHitWall = true;
                fDistanceToWall = fDepth;
            } else {
                char currentCell = dungeon[nTestY][nTestX];
                if (currentCell == '#' || currentCell == 'B' || currentCell == 'G' || currentCell == 'E' || currentCell == 'O' || currentCell == 'L'|| currentCell == 'S') {
                    bHitWall = true;
                    vector<pair<float, float>> corners;
                    for (int tx = 0; tx < 2; tx++) {
                        for (int ty = 0; ty < 2; ty++) {
                            float vx = (float)nTestX + tx - fPlayerX;
                            float vy = (float)nTestY + ty - fPlayerY;
                            float d = sqrt(vx * vx + vy * vy);
                            float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
                            corners.push_back(make_pair(d, dot));
                        }
                    }
                    sort(corners.begin(), corners.end());
                    float fBound = 0.003f;
                    if (acos(corners[0].second) < fBound) bBoundary = true;
                    if (acos(corners[1].second) < fBound) bBoundary = true;
                    if (acos(corners[2].second) < fBound) bBoundary = true;
                }
            }
        }
        int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall);
        int nFloor = nScreenHeight - nCeiling;
        short nShade;
        if (fDistanceToWall <= fDepth / 4.0f)       nShade = 0x2588;
        else if (fDistanceToWall < fDepth / 3.0f)   nShade = 0x2593;
        else if (fDistanceToWall < fDepth / 2.0f)   nShade = 0x2592;
        else if (fDistanceToWall < fDepth)          nShade = 0x2591;
        else                                        nShade = ' ';
        if (bBoundary) nShade = '|';

        short mShade;
        for (int y = 0; y < nScreenHeight; y++) {
            if (y < nCeiling)
                screen[y * nScreenWidth + x] = ' ';
            else if (y > nCeiling && y <= nFloor)
                screen[y * nScreenWidth + x] = nShade;
            else {
                float b = 1.0f - (((float)y - nScreenHeight / 2.0f) / ((float)nScreenHeight / 2.0f));
                if (b < 0.25)       mShade = '#';
                else if (b < 0.5)   mShade = 'x';
                else if (b < 0.75)  mShade = '.';
                else if (b < 0.9)   mShade = '-';
                else                mShade = ' ';
                screen[y * nScreenWidth + x] = mShade;
            }
        }
    }




// update to display player gold, stats
    swprintf_s(screen, 100,
               L"X=%3.2f, Y=%3.2f, Armor=%d, Health=%d/%d, Gold=%d",
               fPlayerX, fPlayerY, player->getArmor(), player->getCurrentHealth(),
               player->getMaxHealth(), player->getGold()
               //, currentFloor, currentLevel
               );
    for (int nx = 0; nx < nMapHeight; nx++) {
        for (int ny = 0; ny < nMapWidth; ny++) {
            screen[(ny + 1) * nScreenWidth + nx] = dungeon[ny][nx];
        }
    }
    screen[((int)fPlayerY + 1) * nScreenWidth + (int)fPlayerX] = 'P';
    screen[nScreenWidth * nScreenHeight - 1] = '\0';
    WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, {0, 0}, &dwBytesWritten);
}

// Residual leftover code that might be useful someday
// Leftover from attempt at advanced combat system
//Monster* getMonsterFromDungeonCoords(char dungeon[][DUNGEON_SIZE], Monster* monsters[MONSTER_COUNT], int x, int y){
//    for (int i = 0; i < DUNGEON_SIZE; i++){
//        for (int j = 0; j < DUNGEON_SIZE; j++){
//            if (dungeon[x][y] == dungeon[monsters[i]->getDungeonX()][monsters[i]->getDungeonY()]){
//                return monsters[i];
//            }
//        }
//    }
//
//return nullptr;
//}
//        // if Player is in monster cell
//        if (x >= monsterX && y < monsterY) {
//            bool monsterTurn = false;
//            Monster* monsterInCell = getMonsterFromDungeonCoords(dungeon, monsters, x, y);
//            if (monsterInCell != nullptr && dungeon[x][y] == monsterInCell->getLetter()) {
//                // set to zero for testing purposes
//                // int enemyChanceToHit = randRange(0, 10);
//                //if (enemyChanceToHit > 6){
//                int damageToPlayer = monsterInCell->getDamage();
//                if (player->getArmor() > 0){
//                    player->setArmor(player->getArmor() - damageToPlayer);
//                } else {
//                    player->setCurrentHealth(player->getCurrentHealth() - damageToPlayer);
//                }
//                // }
//                /// curly bracket might not have gone here
//                monsterTurn = true;
//            }
//            if (monsterTurn) {
//                monsterInCell->setHealth(monsterInCell->getHealth() - player->getDamage());
//                if (monsterInCell->getHealth() <= 0){
//                    dungeon[x][y] = '_';
//                    delete monsterInCell;
//                }
//            }
//            combatHappened = true;
//        }

// I can;t figure out combat
// If I walk in to a monster it whacks me until I die and the game crashes.
// Heres what I want to have happen:

//if monster is on a tile (say, dungeon[4][5])
//while (fplayerX is greater than monster->dungeonX
// and less than monster->dungeonX + 1
// (indicating that the player is in the floating value of dungeon[4][x])
//and
//fplayerY is greater than monster->dungeonY
// and less than monster->dungeonY + 1
//(indicating that the player is in the floating value of dungeon[x][5])
//combatHappened = true;
//     }