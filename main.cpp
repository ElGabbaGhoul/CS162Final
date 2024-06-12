#include <iostream>
#include <Windows.h>
#include <chrono>
#include "GraphicsEngine.hpp"
#include "RandomGeneration.hpp"
#include "MonsterClass.hpp"

Player* player;

// "Draxon's Dungeon"

// Axel
// Draxon
// Elyra

int main() {
    char dungeon[DUNGEON_SIZE][DUNGEON_SIZE];
    int bLoc[2], gLoc[2], eLoc[2], mLoc[2];
    char itemChar = '_';

    player = new Player("Player1", 5, 2, 3, 3, 0);

    std::string playerName = getCharName();

    player->setName(playerName);

    Monster* monsters[MONSTER_COUNT];


    std::cout << "Greetings, " << player->getName() << ".\n" << std::endl;
    //twoSecPause();
    std::cout << "\n";
    createDungeon(dungeon, bLoc, gLoc, eLoc, mLoc, BOMBS, GOLD, itemChar, monsters);
    displayDungeon(dungeon);
    system("pause");

    InitializeFPS();

    float prevX = fPlayerX;
    float prevY = fPlayerY;

    wchar_t* screen = new wchar_t[nScreenWidth * nScreenHeight];
    HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, nullptr, CONSOLE_TEXTMODE_BUFFER, nullptr);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cout << "Failed to create console screen buffer" << std::endl;
        return 1;
    }
    SetConsoleActiveScreenBuffer(hConsole);
    ShowWindow(GetConsoleWindow(), SW_SHOW);
    DWORD dwBytesWritten = 0;

    auto tp1 = std::chrono::system_clock::now();
    auto tp2 = std::chrono::system_clock::now();

    // game loop
    bool bGameRunning = true;
    while (bGameRunning) {
        tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> elapsedTime = tp2 - tp1;
        tp1 = tp2;
        float fElapsedTime = elapsedTime.count();

        UpdatePlayer(fElapsedTime, dungeon, prevX, prevY);
        checkTile(dungeon, player, monsters, prevX, prevY);
        RenderFrame(screen, dungeon, hConsole, dwBytesWritten, fElapsedTime);

        // gameOver cases
        if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            bGameRunning = false;
        if (player->getCurrentHealth() == 0)
            bGameRunning = false;

    }


    // clean up allocated monsters
    for (int i = 0; i < MONSTER_COUNT; ++i){
        delete monsters[i];
    }

    // delete player.
    // Once you die, it's game over.
    // NO character saves. (At this point)
    delete player;

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