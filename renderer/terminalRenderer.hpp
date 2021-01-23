#ifndef TERMINALRENDERER_HPP
#define TERMINALRENDERER_HPP

#include <vector>
#include <ctime>

#include "../shapes/shapes.hpp"

class TerminalRenderer {
public:
    TerminalRenderer(int ww, int hh);

    void renderRect(Rect rect);
    void renderPoint(Point point);
    void renderString(Point pos, std::string str);

    void display();

private:
    int w, h;
    double fps;
    std::clock_t lastFrame;
    Rect renderBox;
    std::vector<std::vector<char>> mapBuffer;

    void clearBuffer();
};

#endif // TERMINALRENDERER_HPP