#include <iostream>
#include <tuple>
#include <array>
#include <vector>
#include <cmath>
#include <windows.h>
#include <fstream>

#include "shapes/shapes.hpp"
#include "renderer/terminalRenderer.hpp"
#include "games/pong.hpp"

#pragma comment(lib, "User32.lib")


using namespace std;

struct games {
    int total;
    int p1;
    int p2;
};

tuple<int, int> getTerminalSize();
void hideCursor();
void saveGamesCount(bool player);
void startGame();
void displayStatsFromfile();


int main() {
    cout << endl << endl << "Welcome to pong game by Leon Czajka" << endl << endl;
    cout << "When in game, tap Q to exit" << endl << endl;
    cout << "You have two options to choose:" << endl;
    cout << "play - start game" << endl;
    cout << "stats - display played games statistics" << endl;
    cout << "if you type something different we are starting the game" << endl;

    string option;
    cin >> option;

    if (option == "play") {
        startGame();
    } else if (option == "stats") {
        displayStatsFromfile();
    } else {
        startGame();
    }

    return 0;
}

tuple<int, int> getTerminalSize() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int columns, rows;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    return make_tuple(columns, rows - 1);
}

void hideCursor() {
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

void saveGamesCount(bool player) {
    ofstream binFile("games.bin", ios::binary);
    fstream strFile("games.txt", ios::out | ios::in);

    games game;
    strFile >> game.total >> game.p1 >> game.p2;

    strFile.clear();
    strFile.seekg(0, ios::beg);

    if (player) strFile << game.total + 1 << endl <<  game.p1 + 1 << endl << game.p2;
    else strFile << game.total + 1 << endl <<  game.p1 << endl << game.p2 + 1;

    strFile.close();

    int data = game.total + game.p1 + game.p2;
    binFile.write((const char*) &data, sizeof data);
    binFile.close();
}

void startGame() {
    auto [x, y] = getTerminalSize();
    Pong pong(x, y);

    hideCursor();

    ios::sync_with_stdio(false);

    auto counter = 0;
    while(!GetAsyncKeyState('Q')) {

        if (counter % 30 == 0) {
            if (GetAsyncKeyState(VK_UP)) {
                pong.mvP2(1);
            } else if (GetAsyncKeyState(VK_DOWN)) {
                pong.mvP2(0);
            }

            if (GetAsyncKeyState('W')) {
                pong.mvP1(1);
            } else if (GetAsyncKeyState('S')) {
                pong.mvP1(0);
            }
            pong.mvP1();
            pong.mvP2();
            int endGame = pong.game();
            if(endGame == 1) {
                saveGamesCount(false);
                return;
            } else if (endGame == 2) {
                saveGamesCount(true);
                return;
            }
        }
        counter ++;
        Sleep(1);
    }
}

void displayStatsFromfile() {
    fstream strFile("games.txt", ios::in);

    games game;

    strFile >> game.total >> game.p1 >> game.p2;

    cout << endl << endl << "Total games played so far: " << game.total << endl;
    cout << "Games won by player one: " << game.p1 << endl;
    cout << "Games won by player two: " << game.p2 << endl;

    strFile.close();
}