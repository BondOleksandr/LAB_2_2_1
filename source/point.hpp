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
    Point(double x, double y);

    double getX() const;
    double getY() const;

    void setX(double newX);
    void setY(double newY);

    void printInfo() const;
    static Point GEN();                              // Generates a point with random coordinates
    void shift(double dx, double dy);                // Shifts point by dx, dy
    static bool isOnLine(const Point& a, const Point& b, const Point& c); // Checks if c lies on line ab
};