//
// Created by Scooter on 6/2/2024.
//

#ifndef CSFINAL_GRAPHICSENGINE_HPP
#define CSFINAL_GRAPHICSENGINE_HPP

#include <Windows.h>
#include "RandomGeneration.hpp"
#include "MonsterClass.hpp"
#include <vector>
#include <chrono>

extern Player* player;

extern int nScreenWidth;
extern int nScreenHeight;

extern float fPlayerX;
extern float fPlayerY;
extern float fPlayerA;

extern int nMapHeight;
extern int nMapWidth;

extern float fFOV;
extern float fDepth;

void InitializeFPS();
void UpdatePlayer(float fElapsedTime, const char dungeon[][16]);
void checkTile(char dungeon[][DUNGEON_SIZE], Player* playerPtr);
void RenderFrame(wchar_t* screen, const char dungeon[][16], HANDLE hConsole, DWORD& dwBytesWritten, float fElapsedTime);

#endif //CSFINAL_GRAPHICSENGINE_HPP
