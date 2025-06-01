#include "line.hpp"

Line::Line(const Point& a, const Point& b) : BEG(a), END(b) {}

Point Line::getPointBEG() const {
    return BEG;
}

Point Line::getPointEND() const {
    return END;
}

void Line::printInfo() const {
    cout << "Line defined by points: " << endl;
    BEG.printInfo();
    END.printInfo();
}

Line Line::GEN() {
    Point beg = beg.GEN();
    Point end = end.GEN();
    Line C(beg, end);
    return C;
}

bool Line::isParalel(const Line& z, Line& u) {
    return (((z.END.getX() - z.BEG.getX()) / (z.END.getY() - z.BEG.getY())) ==
            ((u.END.getX() - u.BEG.getX()) / (u.END.getY() - u.BEG.getY())));
}

Point Line::crossing(const Line& z, Line& u) {//fixed after unit-testing
    Point Crossing_point(0, 0);
    double a1 = z.END.getY() - z.BEG.getY();
    double b1 = z.BEG.getX() - z.END.getX();
    double c1 = a1 * z.BEG.getX() + b1 * z.BEG.getY();

    double a2 = u.END.getY() - u.BEG.getY();
    double b2 = u.BEG.getX() - u.END.getX();
    double c2 = a2 * u.BEG.getX() + b2 * u.BEG.getY();

    double det = a1 * b2 - a2 * b1;

    if (det == 0) {
        Crossing_point.setX(14);
        Crossing_point.setY(88);
    }
    else {
        double x = (b2 * c1 - b1 * c2) / det;
        double y = (a1 * c2 - a2 * c1) / det;
        Crossing_point.setX(x);
        Crossing_point.setY(y);
    }
    return Crossing_point;
}

double Line::angle(const Line& z, Line& u) {
    double ax = z.END.getX() - z.BEG.getX();
    double ay = z.END.getY() - z.BEG.getY();
    double bx = u.END.getX() - u.BEG.getX();
    double by = u.END.getY() - u.BEG.getY();
    return acos((ax * bx + ay * by) / (sqrt(ax * ax + ay * ay) * sqrt(bx * bx + by * by)));
}

double Line::LLength(const Line& z) {
    double ax = z.END.getX() - z.BEG.getX();
    double ay = z.END.getY() - z.BEG.getY();
    return sqrt(ax * ax + ay * ay);
}
