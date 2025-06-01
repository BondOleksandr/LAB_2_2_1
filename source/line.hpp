#pragma once
#include <iostream>
#include <cmath>
#include "point.hpp"

using namespace std;

class Line {
private:
    Point BEG;
    Point END;

public:
    Line(const Point& a, const Point& b);

    Point getPointBEG() const;
    Point getPointEND() const;
    void printInfo() const;

    static Line GEN();                                 // Generates a line from random points
    static bool isParalel(const Line& z, Line& u);      // Checks if two lines are parallel
    static Point crossing(const Line& z, Line& u);      // Returns point of intersection
    static double angle(const Line& z, Line& u);        // Returns angle between two lines in radians
    static double LLength(const Line& z);               // Returns length of the line
};