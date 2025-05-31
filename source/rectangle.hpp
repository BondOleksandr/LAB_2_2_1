#pragma once

#include <iostream>
#include <cmath>
#include "point.hpp"
#include "line.hpp"
#include "figure.hpp"

class Rectangle : public Figure {
private:
    Point a;
    Point b;
    Point c;
    Point d;
public:
    Rectangle(const Point& a, const Point& b, const Point& c, const Point& d) : a(a), b(b), c(c), d(d) {}

    Point getA() const { return a; }
    Point getB() const { return b; }
    Point getC() const { return c; }
    Point getD() const { return d; }

    void setA(const Point& newA) { a = newA; }
    void setB(const Point& newB) { b = newB; }
    void setC(const Point& newC) { c = newC; }
    void setD(const Point& newD) { d = newD; }

    static Rectangle GEN() {
        Point A = A.GEN();
        Point B = B.GEN();
        Point C = C.GEN();
        Point D = D.GEN();
        Rectangle ABCD(A, B, C, D);
        return ABCD;
    }

    void printInfo() const override {
        cout << "Rectangle with vertices: "<<endl;
        a.printInfo();
        b.printInfo();
        c.printInfo();
        d.printInfo();
    }

    void shift(double dx, double dy) override {
        a.shift(dx, dy);
        b.shift(dx, dy);
        c.shift(dx, dy);
        d.shift(dx, dy);
    }
    
    static bool isconvex(const Rectangle& ABCD) {//returns 1, if rectangle is convex (opukliy), 0 if not
        Line AB(ABCD.a, ABCD.b);
        Line AD(ABCD.a, ABCD.d);
        Line BC(ABCD.b, ABCD.c);
        Line CD(ABCD.c, ABCD.d);
        double r = Line::angle(AB, AD) + Line::angle(AD, CD) + Line::angle(BC, CD) + Line::angle(BC, AB);
        if (r < 6.290 && r > 6.280)return true;
        return false;
    }

    static double perimeter(const Rectangle& ABCD) {//returns perimeter of the rectangle
        Line AB(ABCD.a, ABCD.b);
        Line AD(ABCD.a, ABCD.d);
        Line BC(ABCD.b, ABCD.c);
        Line CD(ABCD.c, ABCD.d);
        return Line::LLength(AB) + Line::LLength(AD) + Line::LLength(BC) + Line::LLength(CD);
    }

    static double area(const Rectangle& ABCD) {//returns area of the rectangle (through diagonal and sin between them)
        Line AC(ABCD.a, ABCD.c);
        Line BD(ABCD.b, ABCD.d);
        double ACl = Line::LLength(AC);
        double BDl = Line::LLength(BD);
        double sinus = sin(Line::angle(AC, BD));
        return ACl * BDl * sinus;
    }

};