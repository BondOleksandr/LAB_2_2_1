#pragma once

#include "figure.hpp"
#include "point.hpp"

class Circle : public Figure {
private:
    Point center;
    double r;

public:
    Circle(const Point& cent, double r);

    Point getO() const;
    double getR() const;

    void setO(Point newCenter);
    void setR(double newR);

    void shift(double dx, double dy) override;
    void printInfo() const override;

    static double area(const Circle& CL);
    static double perimeter(const Circle& CL);
    static Circle GEN();
};
