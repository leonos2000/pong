#include <iostream>
#include <tuple>
#include <array>
#include <vector>
#include <cmath>
#include <windows.h>

#include "shapes/shapes.hpp"
#include "renderer/terminalRenderer.hpp"
#include "games/pong.hpp"

#pragma comment(lib, "User32.lib")


std::tuple<int, int> getTerminalSize();
void hideCursor();


int main() {

    auto [x, y] = getTerminalSize();
    Pong pong(x, y);

    hideCursor();

    std::ios::sync_with_stdio(false);

    auto counter = 0;
    
    while(!GetAsyncKeyState('Q')) {


        if (counter % 20 == 0) {
            if (GetAsyncKeyState(VK_UP)) {
                pong.mvP2(1);
            } else if (GetAsyncKeyState(VK_DOWN)) {
                pong.mvP2(0);
            }
        }

        // if (GetAsyncKeyState('W')) {
        //     pong.mvP1(1);
        // } else if (GetAsyncKeyState('S')) {
        //     pong.mvP1(0);
        // }
        if (counter % 30 == 0) {
            pong.mvP1();
            pong.game();
        }
        counter ++;
        Sleep(1);
    }

    return 0;
}

std::tuple<int, int> getTerminalSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return std::make_tuple(columns, rows - 1);
}

void hideCursor() {
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}