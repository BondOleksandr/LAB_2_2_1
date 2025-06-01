#include "point.hpp"

Point::Point(double x, double y) : x(x), y(y) {}

double Point::getX() const {
    return x;
}

double Point::getY() const {
    return y;
}

void Point::setX(double newX) {
    x = newX;
}

void Point::setY(double newY) {
    y = newY;
}

void Point::printInfo() const {
    cout << "Point (" << x << ", " << y << ")" << endl;
}

Point Point::GEN() {
    Point A(0, 0);
    A.setX(dis(gen) * (rand() % 100));
    A.setY(dis(gen) * (rand() % 100));
    return A;
}

void Point::shift(double dx, double dy) {
    x += dx;
    y += dy;
}

bool Point::isOnLine(const Point& a, const Point& b, const Point& c) {
    return ((c.getX() - a.getX()) * (b.getY() - a.getY())) ==
           ((c.getY() - a.getY()) * (b.getX() - a.getX()));
}