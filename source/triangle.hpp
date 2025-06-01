#pragma once

#include <iostream>
#include <cmath>
#include "point.hpp"
#include "line.hpp"
#include "figure.hpp"

class Triangle : public Figure {
private:
    Point a, b, c;

public:
    Triangle(const Point& a, const Point& b, const Point& c);

    Point getA() const;
    Point getB() const;
    Point getC() const;

    void setA(const Point& newA);
    void setB(const Point& newB);
    void setC(const Point& newC);

    static Triangle GEN();                         // Generates random triangle

    void printInfo() const override;
    void shift(double dx, double dy) override;     // Applies shift to all vertices

    static double area(const Triangle& ABC);       // Calculates area using two sides and sine of angle
    static Point outcircle(const Triangle& ABC);   // Returns circumcenter of triangle
    static Point incircle(const Triangle& ABC);    // Returns incenter of triangle
    static double perimeter(const Triangle& ABC);  // Calculates triangle perimeter
    static bool issimilar(const Triangle& ABC, const Triangle& XYZ); // Checks similarity
};