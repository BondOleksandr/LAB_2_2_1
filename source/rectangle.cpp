#include "rectangle.hpp"

Rectangle::Rectangle(const Point& a, const Point& b, const Point& c, const Point& d)
    : a(a), b(b), c(c), d(d) {}

Point Rectangle::getA() const { return a; }
Point Rectangle::getB() const { return b; }
Point Rectangle::getC() const { return c; }
Point Rectangle::getD() const { return d; }

void Rectangle::setA(const Point& newA) { a = newA; }
void Rectangle::setB(const Point& newB) { b = newB; }
void Rectangle::setC(const Point& newC) { c = newC; }
void Rectangle::setD(const Point& newD) { d = newD; }

Rectangle Rectangle::GEN() {
    Point A = A.GEN();
    Point B = B.GEN();
    Point C = C.GEN();
    Point D = D.GEN();
    return Rectangle(A, B, C, D);
}

void Rectangle::printInfo() const {
    cout << "Rectangle with vertices: " << endl;
    a.printInfo();
    b.printInfo();
    c.printInfo();
    d.printInfo();
}

void Rectangle::shift(double dx, double dy) {
    a.shift(dx, dy);
    b.shift(dx, dy);
    c.shift(dx, dy);
    d.shift(dx, dy);
}

bool Rectangle::isconvex(const Rectangle& ABCD) {
    Line AB(ABCD.a, ABCD.b);
    Line AD(ABCD.a, ABCD.d);
    Line BC(ABCD.b, ABCD.c);
    Line CD(ABCD.c, ABCD.d);
    double r = Line::angle(AB, AD) + Line::angle(AD, CD) + Line::angle(BC, CD) + Line::angle(BC, AB);
    return (r < 6.290 && r > 6.280);
}

double Rectangle::perimeter(const Rectangle& ABCD) {
    Line AB(ABCD.a, ABCD.b);
    Line AD(ABCD.a, ABCD.d);
    Line BC(ABCD.b, ABCD.c);
    Line CD(ABCD.c, ABCD.d);
    return Line::LLength(AB) + Line::LLength(AD) + Line::LLength(BC) + Line::LLength(CD);
}

double Rectangle::area(const Rectangle& ABCD) {//fixed after unit testing
    Line AC(ABCD.a, ABCD.c);
    Line BD(ABCD.b, ABCD.d);
    double ACl = Line::LLength(AC);
    double BDl = Line::LLength(BD);
    double sinus = sin(Line::angle(AC, BD));
    return 0.5 * ACl * BDl * sinus;
}
