#include "circle.hpp"
#include "RNG.hpp"
#include <iostream>
#include <cmath>

Circle::Circle(const Point& cent, double r) : center(cent), r(r) {}

Point Circle::getO() const { return center; }
double Circle::getR() const { return r; }

void Circle::setO(Point newCenter) { center = newCenter; }
void Circle::setR(double newR) { r = newR; }

void Circle::shift(double dx, double dy) {
    center.shift(dx, dy);
}

void Circle::printInfo() const {
    std::cout << "Circle with center: " << std::endl;
    center.printInfo();
    std::cout << "and radius " << r << std::endl;
}

double Circle::area(const Circle& CL) {
    return CL.r * CL.r * 3.141592;
}

double Circle::perimeter(const Circle& CL) {
    return 2 * CL.r * 3.141592;
}

Circle Circle::GEN() {
    Point CENTR = Point::GEN();
    double rad = dis(gen) * (rand() % 100);
    return Circle(CENTR, rad);
}
