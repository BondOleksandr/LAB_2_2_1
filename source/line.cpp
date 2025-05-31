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
    Line(const Point& a, const Point& b) : BEG(a), END(b) {}

    Point getPointBEG() const { return BEG; }
    Point getPointEND() const { return END; }

    void printInfo() const {
        cout << "Line defined by points: " << endl;
        BEG.printInfo();
        END.printInfo();
    }

    static Line GEN() {
        Point beg = beg.GEN();
        Point end = end.GEN();
        Line C(beg, end);
        return C;
    }

    static bool isParalel(const Line& z, Line& u) {//Returns 1, if lines are parallel, else 0
        return(((z.END.getX() - z.BEG.getX()) / (z.END.getY() - z.BEG.getY())) == ((u.END.getX() - u.BEG.getX()) / (u.END.getY() - u.BEG.getY())));
    }

    static Point crossing(const Line& z, Line& u) {//point of the crossing of 2 lines
        Point Crossing_point(0, 0);
        if (isParalel(z, u)) {
            Crossing_point.setX(14);
            Crossing_point.setY(88);
        }
        else {
            double c1 = (z.END.getY() - z.BEG.getY()) / (z.END.getX() - z.BEG.getX());
            double c2 = (u.END.getY() - u.BEG.getY()) / (u.END.getX() - u.BEG.getX());
            Crossing_point.setX((u.BEG.getY() - z.END.getY() + z.BEG.getX() * c1 - u.BEG.getX() * c2) / (c1 - c2));
            Crossing_point.setY(((Crossing_point.getX() - z.BEG.getX()) * c1) + z.BEG.getY());
        }
        return Crossing_point;
    }

    static double angle(const Line& z, Line& u) {//As angle between vectors, that are designated by the 2 points of the line
        double ax = z.END.getX() - z.BEG.getX();
        double ay = z.END.getY() - z.BEG.getY();
        double bx = u.END.getX() - u.BEG.getX();
        double by = u.END.getY() - u.BEG.getY();
        return acos((ax * bx + ay * by) / (sqrt(ax * ax + ay * ay) * sqrt(bx * bx + by * by)));
    }

    static double LLength(const Line& z) {//Lenght of vector between 2 defining points
        double ax = z.END.getX() - z.BEG.getX();
        double ay = z.END.getY() - z.BEG.getY();
        return sqrt(ax * ax + ay * ay);
    }
};