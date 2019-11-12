#include <iostream>


#include "pong.hpp"
#include "../renderer/terminalRenderer.hpp"
#include "../shapes/shapes.hpp"


Pong::Pong(int ww, int hh) : TerminalRenderer(ww, hh), w(ww), h(hh) {

    int playerW = ww / 50;
    if(playerW == 0) playerW = 1;

    int playerH = hh / 6;

    Point p1Pos(playerW, (hh - playerH) / 2);
    Point pSize(playerW, playerH);

    p1 = Rect(p1Pos, pSize);

    // std::cout << "P1 size: " << p1Pos.x << " " << p1Pos.y << " " << pSize.x << " " << pSize.y << std::endl;
    // std::cout << "Rect data: " << p1.getSize().x << " " << p1.getSize().y << std::endl;

    Point p2Pos(ww - (ww / 25), (hh - playerH) / 2);

    p2 = Rect(p2Pos, pSize);

    ball.setPos(w / 2, h / 2);

    mvBallx = -1;
    mvBally = 1;

    ballBox = Rect(Point(p1.p2.x - 1, 0), Point(p2.p1.x, h));
    gameBox = Rect(0, 0, w, h);
    // std::cout << "p1: " << p1.p2.x;
    // int t;
    // std::cin >> t;
}

void Pong::game() {
    mvBall();
    renderPoint(ball);
    renderRect(p1);
    renderRect(p2);
    display();
}

void Pong::mvP1(bool upDown) {
    if (upDown) {
        if (p1.p1.y - 1 >= 0)
            p1.translation(0, -1);
    } else if (p1.p2.y + 1 <= h) {
        p1.translation(0, 1);
    }
}

void Pong::mvP1() {
    p1.safeTranslation(0, ball.y - (p1.p2.y - p1.p1.y) - p1.p1.y, gameBox);
}
 
void Pong::mvP2(bool upDown) {
    if (upDown) {
        if (p2.p1.y - 1 >= 0)
            p2.translation(0, -1);
    } else if (p2.p2.y + 1 <= h) {
        p2.translation(0, 1);
    }
}

void Pong::mvBall() {
    switch (ball.safeTranslation(mvBallx, mvBally, ballBox)) {
        case 1:
            mvBally = 1;
            break;
        case 2:
            mvBally = -1;
            break;
        case 3:
            if (p1.p1.y <= ball.y && p1.p2.y >= ball.y ) {
                mvBallx = 1;
            } else {
                renderString(Point(10, 10), "TESTOWY\nSTRING\nOK?");
                display();
                while(1);
            }
            break;
        case 4:
            if (p2.p1.y <= ball.y && p2.p2.y >= ball.y ) {
                mvBallx = -1;
            } else {
                renderString(Point(10, 10), "TESTOWY\nSTRING\nOK?");
                display();
                while(1);
            }
            break;
        default:
            break;
    }
}