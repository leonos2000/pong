#ifndef PONG_HPP
#define PONG_HPP

#include "../shapes/shapes.hpp"
#include "../renderer/terminalRenderer.hpp"

class Pong : TerminalRenderer{
public:
    Pong(int ww, int hh);

    void game();

    void mvP1();
    void mvP1(bool upDown);

    void mvP2(bool upDown);

    void mvBall();

private:
    int w, h, mvBallx, mvBally;
    Point ball;
    Rect p1, p2, ballBox, gameBox;
};

#endif // PONG_HPP