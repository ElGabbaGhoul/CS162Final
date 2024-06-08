#include <iostream>
#include <Windows.h>
#include <chrono>
#include "GraphicsEngine.hpp"
#include "RandomGeneration.hpp"

int main() {
    char dungeon[DUNGEON_SIZE][DUNGEON_SIZE];
    int bLoc[2], gLoc[2], eLoc[2], pLoc[2], mLoc[2], pLocNew[2];
    char itemChar = '_';
    std::string charName;
    int charGold = 0;


    charName = getCharName();
    std::cout << "Greetings, " << charName << ".\n" << std::endl;
    twoSecPause();
    std::cout << "\n";
    createDungeon(dungeon, bLoc, gLoc, eLoc, mLoc, BOMBS, GOLD, MONSTERS, itemChar);
    displayDungeon(dungeon);
    system("pause");

    std::cout << "Program started" << std::endl;

    InitializeFPS();

    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to create console screen buffer" << std::endl;
        return 1;
    }
    SetConsoleActiveScreenBuffer(hConsole);
    ShowWindow(GetConsoleWindow(), SW_SHOW);
    DWORD dwBytesWritten = 0;

    std::cout << "Screen buffer created" << std::endl;
    displayDungeon(dungeon);

    auto tp1 = std::chrono::system_clock::now();
    auto tp2 = std::chrono::system_clock::now();

    bool bGameRunning = true;
    while (bGameRunning) {
        tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float fElapsedTime = elapsedTime.count();

        UpdatePlayer(fElapsedTime, dungeon);
        RenderFrame(screen, dungeon, hConsole, dwBytesWritten, fElapsedTime);

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