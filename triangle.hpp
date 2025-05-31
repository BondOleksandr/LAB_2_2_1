#pragma once
#include "point.hpp"
#include "line.hpp"

class Triangle : public Figure {
private:
    Point a;
    Point b;
    Point c;

public:
    Triangle(const Point& a, const Point& b, const Point& c) : a(a), b(b), c(c) {}

    Point getA() const { return a; }
    Point getB() const { return b; }
    Point getC() const { return c; }

    void setA(const Point& newA) { a = newA; }
    void setB(const Point& newB) { b = newB; }
    void setC(const Point& newC) { c = newC; }

    static Triangle GEN() {
        Point A = A.GEN();
        Point B = B.GEN();
        Point C = C.GEN();
        Triangle ABC(A, B, C);
        return ABC;
    }

    void printInfo() const {
        cout << "Triangle with vertices: "<<endl;
        a.printInfo();
        b.printInfo();
        c.printInfo();
    }

    void shift(double dx, double dy) override {
        a.shift(dx, dy);
        b.shift(dx, dy);
        c.shift(dx, dy);
    }

    static double area(const Triangle& ABC) {//return area of the triangle
        Line AB(ABC.a, ABC.b);
        Line AC(ABC.a, ABC.c);
        double ABl = Line::LLength(AB);
        double ACl = Line::LLength(AC);
        double sinus = sin(Line::angle(AB, AC));
        return ABl * ACl * sinus / 2;
    }

    static Point outcircle(const Triangle& ABC) {//returns center of the outer circle
        Point Outercircle_point(0, 0);
        Point x = ABC.a;
        Point y = ABC.b;
        Point z = ABC.c;
        //The next 3 doubles calculations are written by chatgpt
        double D = 2 * (x.getX() * (y.getY() - z.getY()) + y.getX() * (z.getY() - x.getY()) + z.getX() * (x.getY() - y.getY()));

        double Dx = (x.getX() * x.getX() + x.getY() * x.getY()) * (y.getY() - z.getY()) +
            (y.getX() * y.getX() + y.getY() * y.getY()) * (z.getY() - x.getY()) +
            (z.getX() * z.getX() + z.getY() * z.getY()) * (x.getY() - y.getY());

        double Dy = (x.getX() * x.getX() + x.getY() * x.getY()) * (z.getX() - y.getX()) +
            (y.getX() * y.getX() + y.getY() * y.getY()) * (x.getX() - z.getX()) +
            (z.getX() * z.getX() + z.getY() * z.getY()) * (y.getX() - x.getX());

        Outercircle_point.setX(Dx / D);
        Outercircle_point.setY(Dy / D);
        return Outercircle_point;
    }

    static double perimeter(const Triangle& ABC) {//triangle perimeter
        Line AB(ABC.a, ABC.b);
        Line AC(ABC.a, ABC.c);
        Line BC(ABC.c, ABC.b);
        return Line::LLength(AB) + Line::LLength(AC) + Line::LLength(BC);
    }

    static bool issimilar(const Triangle& ABC, const Triangle& XYZ) {//returns 1 if triangles are similar, returns 0 if not
        Line AB(ABC.a, ABC.b);
        Line AC(ABC.a, ABC.c);
        Line BC(ABC.c, ABC.b);
        Line XY(XYZ.a, XYZ.b);
        Line XZ(XYZ.a, XYZ.c);
        Line YZ(XYZ.c, XYZ.b);
        double A1 = Line::angle(AB, AC);
        double B1 = Line::angle(AB, BC);
        double X1 = Line::angle(XY, XZ);
        double Y1 = Line::angle(XY, YZ);
        double Z1 = Line::angle(XZ, YZ);
        if (A1 == X1 || A1 == Y1 || A1 == Z1) {
            if (B1 == X1 || B1 == Y1 || B1 == Z1) return true;
        }
        return false;
    }

    static Point incircle(const Triangle& ABC) {//returns center of the inner circle
        Point Incircle_point(0, 0);
        Point x = ABC.a;
        Point y = ABC.b;
        Point z = ABC.c;
        Line AB(x, y);
        Line AC(x, z);
        Line BC(y, z);
        double ABl = Line::LLength(AB);
        double ACl = Line::LLength(AC);
        double BCl = Line::LLength(BC);

        Incircle_point.setX((BCl * x.getX() + ACl * y.getX() + ABl * z.getX()) / (ABl + BCl + ACl));
        Incircle_point.setY((BCl * x.getY() + ACl * y.getY() + ABl * z.getY()) / (ABl + BCl + ACl));

        return Incircle_point;
    }

};