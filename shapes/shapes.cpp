#include <windows.h>
#include <iostream>
#include <tuple>
#include <array>
#include <vector>
#include <cmath>

#include "shapes.hpp"

std::tuple<int, int> Point::getPos() {
    return std::make_tuple(x, y);
}

void Point::setPos(int xx, int yy) {
    x = xx;
    y = yy;
}

void Point::translation(int tx, int ty) {
    x += tx;
    y += ty;
}

void Point::translationAngle(int len, int angle) {
    x += len * std::cos(angle);
    y += len * std::sin(angle);
}

int Point::safeTranslation(int tx, int ty, Rect rect) {
    if (tx > 0) {   // move right
        if (x + tx >= rect.getSize().x)
            return 4;
        else
            translation(tx, 0);
    } else {    // move left
        if (x + tx <= rect.p1.x)
            return 3;
        else
            translation(tx, 0);
    }
    if (ty > 0) {   // move down
        if (y + ty >= rect.getSize().y)
            return 2;
        else
            translation(0, ty);
    } else {    // move up
        if (y + ty <= rect.p1.y)
            return 1;
        else
            translation(0, ty);
    }
    return 0;
}

Rect::Rect(Point pp1, Point pp2) : p1(pp1) {
    p2 = Point(pp1.x + pp2.x, pp1.y + pp2.y);
}

Rect::Rect(int x, int y, int w, int h) {
    p1 = Point(x, y);
    p2 = Point(x + w, y + h);
}

void Rect::translation(int tx, int ty) {
    p1.translation(tx, ty);
    p2.translation(tx, ty);
}

int Rect::safeTranslation(int tx, int ty, Rect rect) {
    if (tx > 0) {   // move right
        if (p2.safeTranslation(tx, 0, rect) == 0) 
            p1.safeTranslation(tx, 0, rect);
        else return p2.safeTranslation(tx, 0, rect);
    } else {    // move left
        if (p1.safeTranslation(tx, 0, rect) == 0)
            p2.safeTranslation(tx, 0, rect);
        else return p1.safeTranslation(tx, 0, rect);
    }
    if (ty > 0) {   // move down
        if (p2.safeTranslation(0, ty, rect) == 0)
            p1.safeTranslation(0, ty, rect);
        else return p2.safeTranslation(0, ty, rect);
    } else {    //move up
        if (p1.safeTranslation(0, ty, rect) == 0)
            p2.safeTranslation(0, ty, rect);
        else return p1.safeTranslation(0, ty, rect);
    }
    return 0;
}

bool Rect::contain(Point point) {
    return (point.x > p1.x && point.y < p1.y && point.x < p2.x && point.y > p2.y) ? true : false;
}

Point Rect::getSize() {
    return Point(p2.x - p1.x, p2.y - p1.y);
}

Point Rect::getPos() {
    return p1;
}

void Rect::setPos(Point pos) {
    p2.x = pos.x + getSize().x;
    p2.y = pos.y + getSize().y;

    p1.x = pos.x;
    p1.y = pos.y;
}