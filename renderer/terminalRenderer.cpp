#include <iostream>
#include <vector>
#include <windows.h>

#include "terminalRenderer.hpp"
#include "../shapes/shapes.hpp"


TerminalRenderer::TerminalRenderer(int ww, int hh) : w(ww), h(hh) {
    mapBuffer = std::vector<std::vector<char>>(h, std::vector<char>(w));

    renderBox = Rect(0, 0, w, h);
}


void TerminalRenderer::renderRect(Rect rect) {
    for (int i = 0; i < rect.getSize().x; i++) {
        for (int j = 0; j < rect.getSize().y; j++) {
            mapBuffer[j + rect.getPos().y][i + rect.getPos().x] = (char) 219;
        }
    }
}

void TerminalRenderer::renderPoint(Point point) {
    mapBuffer[point.y][point.x] = 'O';
}

void TerminalRenderer::renderString(Point pos, std::string str) {

    auto firstX = pos.x;

    for (auto a : str) {
        if (a == '\n') {
            pos.safeTranslation(0, 1, renderBox);
            pos.x = firstX;
        } else {
            mapBuffer[pos.y][pos.x] = a;
            pos.safeTranslation(1, 0, renderBox);
        }
    }
}

void TerminalRenderer::display() {
    COORD cur = {0, 0};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cur);

    std::string buffer;

    for (auto line : mapBuffer) {
        for (auto a : line) {
            buffer += a;
        }
    }
    std::cout << buffer;
    clearBuffer();
}

void TerminalRenderer::clearBuffer() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            mapBuffer[i][j] = ' ';
        }
    }
}