#ifndef SHAPES_HPP
#define SHAPES_HPP

#include <iostream>


class Rect;

class Point {
public:
    Point(int xx = 0, int yy = 0) : x(xx), y(yy) {};

    std::tuple<int, int> getPos();
    void setPos(int xx, int yy);

    void translation(int tx, int ty);
    void translationAngle(int len, int angle);
    int safeTranslation(int tx, int ty, Rect rect);

    int x, y;    
};


class Rect {
public:
    Rect(Point pp1 = Point(), Point pp2 = Point());
    Rect(int x, int y, int w, int h);

    Point getSize();
    Point getPos();

    void setPos(Point pos);

    void translation(int tx, int ty);
    int safeTranslation(int tx, int ty, Rect rect);

    bool contain(Point point);

    Point p1, p2;
};

#endif // SHAPES_HPP