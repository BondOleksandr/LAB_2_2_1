#pragma once
#include <iostream>
#include <cmath>
#include "RNG.hpp"

using namespace std;

class Point {
private:
    double x;
    double y;

public:

    Point(double x, double y) : x(x), y(y) {}

    double getX() const { return x; }
    double getY() const { return y; }

    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }

    void printInfo() const {
        cout << "Point (" << x << ", " << y << ")" << endl;
    }

    static Point GEN() {
        Point A(0,0);
        A.setX(dis(gen)*(rand()%100));
        A.setY(dis(gen) * (rand() % 100));
        return A;
    }

    void shift(double dx, double dy) {
        x += dx;
        y += dy;
    }

    static bool isOnLine(const Point& a, const Point& b, const Point& c) {// Returns 1 if 3 points are on 1 line, else 0
        return ((c.getX() - a.getX()) * (b.getY() - a.getY())) == ((c.getY() - a.getY()) * (b.getX() - a.getX()));
    }
};