#pragma once

#include <iostream>
#include <cmath>
#include "point.hpp"
#include "line.hpp"
#include "figure.hpp"

class Rectangle : public Figure {
private:
    Point a, b, c, d;

public:
    Rectangle(const Point& a, const Point& b, const Point& c, const Point& d);

    Point getA() const;
    Point getB() const;
    Point getC() const;
    Point getD() const;

    void setA(const Point& newA);
    void setB(const Point& newB);
    void setC(const Point& newC);
    void setD(const Point& newD);

    static Rectangle GEN();                         // Generates random rectangle

    void printInfo() const override;
    void shift(double dx, double dy) override;      // Applies shift to all four points

    static bool isconvex(const Rectangle& ABCD);    // Checks if rectangle is convex
    static double perimeter(const Rectangle& ABCD); // Calculates perimeter
    static double area(const Rectangle& ABCD);      // Calculates area
};