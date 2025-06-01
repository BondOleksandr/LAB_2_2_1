#include "triangle.hpp"

Triangle::Triangle(const Point& a, const Point& b, const Point& c)
    : a(a), b(b), c(c) {}

Point Triangle::getA() const { return a; }
Point Triangle::getB() const { return b; }
Point Triangle::getC() const { return c; }

void Triangle::setA(const Point& newA) { a = newA; }
void Triangle::setB(const Point& newB) { b = newB; }
void Triangle::setC(const Point& newC) { c = newC; }

Triangle Triangle::GEN() {
    Point A = A.GEN();
    Point B = B.GEN();
    Point C = C.GEN();
    return Triangle(A, B, C);
}

void Triangle::printInfo() const {
    cout << "Triangle with vertices: " << endl;
    a.printInfo();
    b.printInfo();
    c.printInfo();
}

void Triangle::shift(double dx, double dy) {
    a.shift(dx, dy);
    b.shift(dx, dy);
    c.shift(dx, dy);
}

double Triangle::area(const Triangle& ABC) {
    Line AB(ABC.a, ABC.b);
    Line AC(ABC.a, ABC.c);
    double ABl = Line::LLength(AB);
    double ACl = Line::LLength(AC);
    double sinus = sin(Line::angle(AB, AC));
    return ABl * ACl * sinus / 2;
}

Point Triangle::outcircle(const Triangle& ABC) {
    Point x = ABC.a;
    Point y = ABC.b;
    Point z = ABC.c;

    double D = 2 * (x.getX() * (y.getY() - z.getY()) +
                    y.getX() * (z.getY() - x.getY()) +
                    z.getX() * (x.getY() - y.getY()));

    double Dx = (x.getX() * x.getX() + x.getY() * x.getY()) * (y.getY() - z.getY()) +
                (y.getX() * y.getX() + y.getY() * y.getY()) * (z.getY() - x.getY()) +
                (z.getX() * z.getX() + z.getY() * z.getY()) * (x.getY() - y.getY());

    double Dy = (x.getX() * x.getX() + x.getY() * x.getY()) * (z.getX() - y.getX()) +
                (y.getX() * y.getX() + y.getY() * y.getY()) * (x.getX() - z.getX()) +
                (z.getX() * z.getX() + z.getY() * z.getY()) * (y.getX() - x.getX());

    Point Outercircle_point(0, 0);
    Outercircle_point.setX(Dx / D);
    Outercircle_point.setY(Dy / D);
    return Outercircle_point;
}

Point Triangle::incircle(const Triangle& ABC) {
    Point x = ABC.a;
    Point y = ABC.b;
    Point z = ABC.c;
    Line AB(x, y);
    Line AC(x, z);
    Line BC(y, z);
    double ABl = Line::LLength(AB);
    double ACl = Line::LLength(AC);
    double BCl = Line::LLength(BC);

    Point Incircle_point(0, 0);
    Incircle_point.setX((BCl * x.getX() + ACl * y.getX() + ABl * z.getX()) / (ABl + BCl + ACl));
    Incircle_point.setY((BCl * x.getY() + ACl * y.getY() + ABl * z.getY()) / (ABl + BCl + ACl));

    return Incircle_point;
}

double Triangle::perimeter(const Triangle& ABC) {
    Line AB(ABC.a, ABC.b);
    Line AC(ABC.a, ABC.c);
    Line BC(ABC.c, ABC.b);
    return Line::LLength(AB) + Line::LLength(AC) + Line::LLength(BC);
}

bool Triangle::issimilar(const Triangle& ABC, const Triangle& XYZ) {
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

    if ((A1 == X1 || A1 == Y1 || A1 == Z1) &&
        (B1 == X1 || B1 == Y1 || B1 == Z1)) {
        return true;
    }

    return false;
}
