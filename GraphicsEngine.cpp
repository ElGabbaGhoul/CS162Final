//
// Created by Scooter on 6/2/2024.
//

#include "GraphicsEngine.hpp"
#include "RandomGeneration.hpp"
#include "MonsterClass.hpp"
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

void checkTile(char dungeon[][DUNGEON_SIZE], Player* player){
    int x = (int)fPlayerY;
    int y = (int)fPlayerX;
    int currentHealth = player->getCurrentHealth();
    int playerGold = player->getGold();
    
    if (dungeon[x][y] == 'B'){
        currentHealth -= 1;
        player->setCurrentHealth(currentHealth);
        dungeon[x][y] = '_';
    } else if (dungeon[x][y] == 'G'){
        playerGold += 5;
        player->setGold(playerGold);
        dungeon[x][y] = '_';
    }
//    else if (dungeon[x][y] = 'M'){
//
//
//
//    }
}


void RenderFrame(wchar_t* screen, const char dungeon[][16], HANDLE hConsole, DWORD& dwBytesWritten, float fElapsedTime) {
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
    swprintf_s(screen, 65, L"X=%3.2f, Y=%3.2f, Gold=%d, Health=%d/%d", fPlayerX, fPlayerY, player->getGold(), player->getCurrentHealth(), player->getMaxHealth());
    for (int nx = 0; nx < nMapHeight; nx++) {
        for (int ny = 0; ny < nMapWidth; ny++) {
            screen[(ny + 1) * nScreenWidth + nx] = dungeon[ny][nx];
        }
    }
    screen[((int)fPlayerY + 1) * nScreenWidth + (int)fPlayerX] = 'P';
    screen[nScreenWidth * nScreenHeight - 1] = '\0';
    WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, {0, 0}, &dwBytesWritten);
}