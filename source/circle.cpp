#pragma once

#include <iostream>
#include <cmath>
#include "point.hpp"
#include "RNG.hpp"
#include "figure.hpp"

using namespace std;

class Circle : public Figure {
private:
    Point center;
    double r;
public:
    Circle(const Point& cent, const double r) : center(center), r(r) {}

    Point getO() const { return center; }
    double getR() const { return r; }

    void setO(Point newCenter) { center = newCenter; }
    void setR(double newR) { r = newR; }

    void shift(double dx, double dy) override {
        center.shift(dx, dy);
    }

    void printInfo() const override {
        cout << "Circle with center: " << endl;
        center.printInfo();
        cout << "and radius " << r << endl;
    }

    static double area(const Circle& CL) {//area of circle
        return (CL.r) * (CL.r) * 3.141592;
    }

    static double perimeter(const Circle& CL) {//perimeter of circle
        return 2 * (CL.r) * 3.141592;
    }

    static Circle GEN() {//changed var names here
        Point CENTR = CENTR.GEN();
        double rad = (dis(gen) * (rand() % 100));
        Circle Circ(CENTR, rad);
        return Circ;
    }

};