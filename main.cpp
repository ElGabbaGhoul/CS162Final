#include <iostream>
#include <Windows.h>
#include <cmath>
#include <chrono>
#include <vector>
#include <algorithm>
#include "RandomGeneration.hpp"

using namespace std;

int nScreenWidth = 120;
int nScreenHeight = 40;

float fPlayerX = 8.0f;
float fPlayerY = 8.0f;
float fPlayerA = 0.0f;

int nMapHeight = 16;
int nMapWidth = 16;

float fFOV = 3.14159f / 4.0f;
float fDepth = 16.0f;

int main() {
    char dungeon[DUNGEON_SIZE][DUNGEON_SIZE];
    int bLoc[2], gLoc[2], eLoc[2], pLoc[2], mLoc[2], pLocNew[2];
    char itemChar = '_';
    std::string charName;
    int charGold = 0;

    charName = getCharName();
    std::cout << "Hello, " << charName<< "." <<std::endl;

    cout << "Program started" << endl;

    if (!GetConsoleWindow()){
        AllocConsole();
    }

    // Create Screen Buffer
    wchar_t *screen = new wchar_t[nScreenWidth*nScreenHeight];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
    if (hConsole == INVALID_HANDLE_VALUE){
        cout << "Failed to create console screen buffer" << endl;
        return 1;
    }
    SetConsoleActiveScreenBuffer(hConsole);
    ShowWindow(GetConsoleWindow(), SW_SHOW);
    DWORD dwBytesWritten = 0;

    cout << "Screen buffer created" << endl;
    createDungeon(dungeon, bLoc, gLoc, eLoc, mLoc, BOMBS, GOLD, MONSTERS, itemChar);
    displayDungeon(dungeon);

    auto tp1 = chrono::system_clock::now();
    auto tp2 = chrono::system_clock::now();

    bool bGameRunning = true;
    while(bGameRunning) {
        cout << "Rendering frame" << endl;

        tp2 = chrono::system_clock::now();
        chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float fElapsedTime = elapsedTime.count();


        if (GetAsyncKeyState((unsigned short)'W') & 0x8000) {
            // Calculate potential new positions
            float newX = fPlayerX + sinf(fPlayerA) * 2.5f * fElapsedTime;
            float newY = fPlayerY + cosf(fPlayerA) * 2.5f * fElapsedTime;

            // Check for collision
            if (dungeon[(int)newY][(int)newX] != '#') {
                // If no collision, update player position
                fPlayerX = newX;
                fPlayerY = newY;
            }
        }

        if (GetAsyncKeyState((unsigned short)'S') & 0x8000) {
            // Calculate potential new positions
            float newX = fPlayerX - sinf(fPlayerA) * 4.0f * fElapsedTime;
            float newY = fPlayerY - cosf(fPlayerA) * 4.0f * fElapsedTime;

            // Check for collision
            if (dungeon[(int)newY][(int)newX] != '#') {
                // If no collision, update player position
                fPlayerX = newX;
                fPlayerY = newY;
            }
        }

        if (GetAsyncKeyState((unsigned short)'A') & 0x8000) {
            fPlayerA -= (1.0f) * fElapsedTime; // Rotate left
        }

        if (GetAsyncKeyState((unsigned short)'D') & 0x8000) {
            fPlayerA += (1.0f) * fElapsedTime; // Rotate right
        }



        // Looking here
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
                    if (dungeon[nTestY][nTestX] == '#') {
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

        swprintf_s(screen, 40, L"X=%3.2f, Y=%3.2f, A=%3.2f FPS=%3.2f ", fPlayerX, fPlayerY, fPlayerA, 1.0f / fElapsedTime);

        for (int nx = 0; nx < nMapWidth; nx++) {
            for (int ny = 0; ny < nMapHeight; ny++) {
                screen[(ny + 1) * nScreenWidth + nx] = dungeon[ny][nx];
            }
        }

        screen[((int)fPlayerY + 1) * nScreenWidth + (int)fPlayerX] = 'P';

        screen[nScreenWidth * nScreenHeight - 1] = '\0';
        WriteConsoleOutputCharacterW(hConsole, screen, nScreenWidth * nScreenHeight, {0, 0}, &dwBytesWritten);

        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            bGameRunning = false;
    }

    return 0;
}
// while invalidName = false
// gets player character name
// do{
// initialize starter dungeon
// displays instructions in the console.
// You are entering [name of dungeon]
// Use WASD to navigate.
// Avoid BOMBS
// Pick up GOLD
// Reach the EXIT
// Have fun! (press any key to continue)
// do {
// displays dungeon
// minimap, player character as P in middle of dungeon
// stats on top bar
// bombs as 1x1x1 B blocks
// monsters as 1x1x1 M blocks
// gold as 1x1x1 G blocks
// exit as 1x1x1 E blocks
// labyrinthine style walls throughout.
// automatic forced instakills will not be implemented.
// you will not encounter a path blocked by a bomb
// } while (gameOver == false)
// } while (replay)