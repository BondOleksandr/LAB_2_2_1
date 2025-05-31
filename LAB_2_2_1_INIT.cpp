#include <iostream>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

random_device rd;  
mt19937 gen(rd()); 
uniform_real_distribution<> dis(0.0, 1.0);

struct ELM {
    double val = 0;
    int row=-1;
    int clmn=-1;
};

struct ELV {
    double val=0;
    int idx=-1;
};

typedef struct MNode {
    double val;
    int row;
    int clmn;
    MNode* next;
}MListn, * MListnp;

typedef struct VNode {
    double val;
    int idx;
    VNode* next;
}VListn, * VListnp;

class Point {
private:
    double x;
    double y;

public:

    Point(double x, double y) : x(x), y(y) {}

    double getX() const { return x; }
    double getY() const { return y; }

    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }

    void printInfo() const {
        cout << "Point (" << x << ", " << y << ")" << endl;
    }

    static Point GEN() {
        Point A(0,0);
        A.setX(dis(gen)*(rand()%100));
        A.setY(dis(gen) * (rand() % 100));
        return A;
    }

    void shift(double dx, double dy) {
        x += dx;
        y += dy;
    }

    static bool isOnLine(const Point& a, const Point& b, const Point& c) {
        return ((c.getX() - a.getX()) * (b.getY() - a.getY())) == ((c.getY() - a.getY()) * (b.getX() - a.getX()));
    }
};

class Line {
private:
    Point a;
    Point b;

public:
    Line(const Point& a, const Point& b) : a(a), b(b) {}

    Point getPointA() const { return a; }
    Point getPointB() const { return b; }

    void printInfo() const {
        cout << "Line defined by points: " << endl;
        a.printInfo();
        b.printInfo();
    }

    static Line GEN() {
        Point A = A.GEN();
        Point B = B.GEN();
        Line C(A, B);
        return C;
    }

    static bool isParalel(const Line& z, Line& u) {//
        return(((z.b.getX() - z.a.getX()) / (z.b.getY() - z.a.getY())) == ((u.b.getX() - u.a.getX()) / (u.b.getY() - u.a.getY())));
    }

    static Point crossing(const Line& z, Line& u) {//point of the crossing of 2 lines
        Point Cr(0, 0);
        if (isParalel(z, u)) {
            Cr.setX(14);
            Cr.setY(88);
        }
        else {
            double c1 = (z.b.getY() - z.a.getY()) / (z.b.getX() - z.a.getX());
            double c2 = (u.b.getY() - u.a.getY()) / (u.b.getX() - u.a.getX());
            Cr.setX((u.a.getY() - z.a.getY() + z.a.getX() * c1 - u.a.getX() * c2) / (c1 - c2));
            Cr.setY(((Cr.getX() - z.a.getX()) * c1) + z.a.getY());
        }
        return Cr;
    }

    static double angle(const Line& z, Line& u) {
        double ax = z.b.getX() - z.a.getX();
        double ay = z.b.getY() - z.a.getY();
        double bx = u.b.getX() - u.a.getX();
        double by = u.b.getY() - u.a.getY();
        return acos((ax * bx + ay * by) / (sqrt(ax * ax + ay * ay) * sqrt(bx * bx + by * by)));
    }

    static double LLength(const Line& z) {
        double ax = z.b.getX() - z.a.getX();
        double ay = z.b.getY() - z.a.getY();
        return sqrt(ax * ax + ay * ay);
    }
};

class Figure {
public:

    virtual void printInfo() const = 0;//polimorp 2 static

    virtual void shift(double dx, double dy) = 0;//polimorph 1 dynamic

    virtual ~Figure() = default;
};

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

    static double area(const Triangle& ABC) {
        Line AB(ABC.a, ABC.b);
        Line AC(ABC.a, ABC.c);
        double ABl = Line::LLength(AB);
        double ACl = Line::LLength(AC);
        double sinn = sin(Line::angle(AB, AC));
        return ABl * ACl * sinn / 2;
    }

    static Point outcircle(const Triangle& ABC) {
        Point O(0, 0);
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

        O.setX(Dx / D);
        O.setY(Dy / D);
        return O;
    }

    static double perimeter(const Triangle& ABC) {
        Line AB(ABC.a, ABC.b);
        Line AC(ABC.a, ABC.c);
        Line BC(ABC.c, ABC.b);
        return Line::LLength(AB) + Line::LLength(AC) + Line::LLength(BC);
    }

    static bool issimilar(const Triangle& ABC, const Triangle& XYZ) {
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

    static Point incircle(const Triangle& ABC) {
        Point O(0, 0);
        Point x = ABC.a;
        Point y = ABC.b;
        Point z = ABC.c;
        Line AB(x, y);
        Line AC(x, z);
        Line BC(y, z);
        double ABl = Line::LLength(AB);
        double ACl = Line::LLength(AC);
        double BCl = Line::LLength(BC);

        O.setX((BCl * x.getX() + ACl * y.getX() + ABl * z.getX()) / (ABl + BCl + ACl));
        O.setY((BCl * x.getY() + ACl * y.getY() + ABl * z.getY()) / (ABl + BCl + ACl));

        return O;
    }

};

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
    
    static bool isconvex(const Rectangle& ABCD) {
        Line AB(ABCD.a, ABCD.b);
        Line AD(ABCD.a, ABCD.d);
        Line BC(ABCD.b, ABCD.c);
        Line CD(ABCD.c, ABCD.d);
        double r = Line::angle(AB, AD) + Line::angle(AD, CD) + Line::angle(BC, CD) + Line::angle(BC, AB);
        if (r < 6.290 && r > 6.280)return true;
        return false;
    }

    static double perimeter(const Rectangle& ABCD) {
        Line AB(ABCD.a, ABCD.b);
        Line AD(ABCD.a, ABCD.d);
        Line BC(ABCD.b, ABCD.c);
        Line CD(ABCD.c, ABCD.d);
        return Line::LLength(AB) + Line::LLength(AD) + Line::LLength(BC) + Line::LLength(CD);
    }

    static double area(const Rectangle& ABCD) {
        Line AC(ABCD.a, ABCD.c);
        Line BD(ABCD.b, ABCD.d);
        double ACl = Line::LLength(AC);
        double BDl = Line::LLength(BD);
        double sinn = sin(Line::angle(AC, BD));
        return ACl * BDl * sinn;
    }

};

class Circle : public Figure {
private:
    Point o;
    double r;
public:
    Circle(const Point& o, const double r) : o(o), r(r) {}

    Point getO() const { return o; }
    double getR() const { return r; }

    void setO(Point newO) { o = newO; }
    void setR(double newR) { r = newR; }

    void shift(double dx, double dy) override {
        o.shift(dx, dy);
    }

    void printInfo() const override {
        cout << "Circle with center: " << endl;
        o.printInfo();
        cout << "and radius " << r << endl;
    }

    static double area(const Circle& CL) {
        return (CL.r) * (CL.r) * 3.141592;
    }

    static double perimeter(const Circle& CL) {
        return 2 * (CL.r) * 3.141592;
    }

    static Circle GEN() {
        Point O = O.GEN();
        double rad = (dis(gen) * (rand() % 100));
        Circle OOO(O, rad);
        return OOO;
    }

};

template <typename PrI>
void printFigureInfo(const PrI& figure) {
    static_assert(is_base_of<Figure, PrI>::value, "T must derive from Figure");
    figure.printInfo();
}

/////////////////////////////////////////////////////////////////MATRIX PART//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double** MATGEN(int size) {
    double** MAT = new double*[size];
    for (int i = 0; i < size; i++) {
        MAT[i] = new double[size];
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((rand() % 100) > 80) {
                MAT[i][j] = (dis(gen) * (rand() % 100));
            }
            else MAT[i][j] = 0;
        }
    }
    return MAT;
}

double* VECGEN(int size) {
    double* VEC = new double[size];
    for (int i = 0; i < size; i++) {
        if ((rand() % 100) > 80) {
            VEC[i] = (dis(gen) * (rand() % 100));
        }
        else VEC[i] = 0;
    }
    return VEC;
}

class MatrixBase {
public:
    virtual void print() = 0;
    virtual ~MatrixBase() = default;
};

class ListMatrix: public MatrixBase {
private:

    MListnp Head;
    int size;

public:

    ListMatrix(int inSize, double** mtx) : size(inSize), Head(nullptr) {
        Head = new MNode;
        MListnp Crnt = NULL;
        bool headmade = false;
        size = inSize;
        Head->val = 0;
        Head->next = NULL;
        Head->row = 0;
        Head->clmn = 0;

        for (int i = 0; i < inSize; i++) {
            for (int j = 0; j < inSize; j++) {
                if (mtx[i][j]) {
                    if (!headmade) {
                        Head->val = mtx[i][j];
                        Head->row = i;
                        Head->clmn = j;
                        Head->next = Crnt;
                        headmade = true;
                        Crnt = Head;
                    }
                    else {
                        MListnp p = new MNode;
                        p->val = mtx[i][j];
                        p->row = i;
                        p->clmn = j;
                        p->next = NULL;
                        Crnt->next = p;
                        Crnt = p;
                    }
                }
            }
        }
    }

    void print() override {
        MListnp crnt = Head;
        bool fin = false;
        for (int i = 0; i < size; i++) {
            cout << endl;
            for (int j = 0; j < size; j++) {
                if (i == crnt->row && j == crnt->clmn && !fin) {
                    cout << crnt->val << " ";
                    if (crnt->next == NULL)fin = true;
                    else crnt = crnt->next;
                }
                else cout << "0 ";
            }
        }
        crnt = NULL;
        delete crnt;
    }

    MListnp Valsearch( double check) {
        if (!check) {
            cout << "Does not work for 0" << endl;
            return NULL;
        }
        MListnp crnt = Head;
        while (crnt) {
            if (crnt->val == check)return crnt;
            else crnt = crnt->next;
        }
        return NULL;
    }

    MListnp INDsearch(int ROW, int CLMN) {
        if (ROW >= size || CLMN >= size) {
            cout << "WRONG INPUT" << endl;
            return NULL;
        }
        MListnp crnt = Head;
        while (crnt) {
            if (crnt->row == ROW && crnt->clmn == CLMN)return crnt;
            if (crnt->row >= ROW && crnt->clmn >= CLMN) {
                crnt = new MNode;
                crnt->val = 0;
                crnt->row = ROW;
                crnt->clmn = CLMN;
                return crnt;
            }
            else crnt = crnt->next;
        }
        crnt = new MNode;
        crnt->val = 0;
        crnt->row = ROW;
        crnt->clmn = CLMN;
        return crnt;
    }
    
    static ListMatrix Summ(ListMatrix A, ListMatrix B) {
        if (!A.Head->val)return B;
        if (!B.Head->val)return A;
        ListMatrix C(0, 0);
        MListnp Ccrnt = new MNode;
        MListnp Acrnt = A.Head;
        MListnp Bcrnt = B.Head;
        C.Head = new MNode;
        C.size = A.size;

        if (A.Head->row > B.Head->row) {
            C.Head->val = B.Head->val;
            C.Head->row = B.Head->row;
            C.Head->clmn = B.Head->clmn;
            C.Head->next = NULL;
            Bcrnt = B.Head->next;
        }
        else {
            if (A.Head->row == B.Head->row) {
                if (A.Head->clmn > B.Head->clmn) {
                    C.Head->val = B.Head->val;
                    C.Head->row = B.Head->row;
                    C.Head->clmn = B.Head->clmn;
                    C.Head->next = NULL;
                    Bcrnt = B.Head->next;
                }
                if (A.Head->clmn == B.Head->clmn) {
                    C.Head->val = B.Head->val+A.Head->val;
                    C.Head->row = B.Head->row;
                    C.Head->clmn = B.Head->clmn;
                    C.Head->next = NULL;
                    Bcrnt = B.Head->next;
                    Acrnt = A.Head->next;
                }
                else {
                    C.Head->val = A.Head->val;
                    C.Head->row = A.Head->row;
                    C.Head->clmn = A.Head->clmn;
                    C.Head->next = NULL;
                    Acrnt = A.Head->next;
                }
            }
            else
            {
                C.Head->val = A.Head->val;
                C.Head->row = A.Head->row;
                C.Head->clmn = A.Head->clmn;
                C.Head->next = NULL;
                Acrnt = A.Head->next;
            }
        }
        Ccrnt = C.Head;
        if (Acrnt && Bcrnt) {
            while ((Acrnt && Bcrnt) && Acrnt->row < Bcrnt->row) {
                MListnp p = new MNode;
                p->val = Acrnt->val;
                p->row = Acrnt->row;
                p->clmn = Acrnt->clmn;
                p->next = NULL;
                Ccrnt->next = p;
                Ccrnt = p;
                Acrnt = Acrnt->next;
            }

            while ((Acrnt && Bcrnt) && Acrnt->row > Bcrnt->row) {
                MListnp p = new MNode;
                p->val = Bcrnt->val;
                p->row = Bcrnt->row;
                p->clmn = Bcrnt->clmn;
                p->next = NULL;
                Ccrnt->next = p;
                Ccrnt = p;
                Bcrnt = Bcrnt->next;
            }

            while ((Acrnt && Bcrnt) && Acrnt->row == Bcrnt->row) {
                while ((Acrnt && Bcrnt) && Acrnt->clmn > Bcrnt->clmn) {
                    MListnp p = new MNode;
                    p->val = Bcrnt->val;
                    p->row = Bcrnt->row;
                    p->clmn = Bcrnt->clmn;
                    p->next = NULL;
                    Ccrnt->next = p;
                    Ccrnt = p;
                    Bcrnt = Bcrnt->next;
                }

                while ((Acrnt && Bcrnt) && Acrnt->clmn < Bcrnt->clmn) {
                    MListnp p = new MNode;
                    p->val = Acrnt->val;
                    p->row = Acrnt->row;
                    p->clmn = Acrnt->clmn;
                    p->next = NULL;
                    Ccrnt->next = p;
                    Ccrnt = p;
                    Acrnt = Acrnt->next;
                }

                while ((Acrnt && Bcrnt) && Acrnt->clmn > Bcrnt->clmn) {
                    MListnp p = new MNode;
                    p->val = Bcrnt->val;
                    p->row = Bcrnt->row;
                    p->clmn = Bcrnt->clmn;
                    p->next = NULL;
                    Ccrnt->next = p;
                    Ccrnt = p;
                    Bcrnt = Bcrnt->next;
                }

                while ((Acrnt && Bcrnt) && Acrnt->clmn == Bcrnt->clmn) {
                    MListnp p = new MNode;
                    p->val = Acrnt->val + Bcrnt->val;
                    p->row = Acrnt->row;
                    p->clmn = Acrnt->clmn;
                    p->next = NULL;
                    Ccrnt->next = p;
                    Ccrnt = p;
                    Acrnt = Acrnt->next;
                    Bcrnt = Bcrnt->next;
                }
            }
        }

        while (Acrnt) {
            MListnp p = new MNode;
            p->val = Acrnt->val;
            p->row = Acrnt->row;
            p->clmn = Acrnt->clmn;
            p->next = NULL;
            Ccrnt->next = p;
            Ccrnt = p;
            Acrnt = Acrnt->next;
        }
        while (Bcrnt) {
            MListnp p = new MNode;
            p->val = Bcrnt->val;
            p->row = Bcrnt->row;
            p->clmn = Bcrnt->clmn;
            p->next = NULL;
            Ccrnt->next = p;
            Ccrnt = p;
            Bcrnt = Bcrnt->next;
        }
        return C;
    }

    void xScalar(ListMatrix A, int x) {
        ListMatrix B(0, 0);
        MListnp crnt = A.Head;
        while (crnt) {
            crnt->val *= x;
            crnt->next;
        }
    }

};

class ListVector : public MatrixBase {
private:

    VListnp Head;
    int size;
    bool row;

public:

    ListVector(int inSize, double* mtx, bool ROW) : size(inSize), Head(nullptr) {
        Head = new VNode;
        VListnp Crnt = Head;
        size = inSize;
        Head->next = NULL;
        Head->idx = 0;
        Head->val = 0;
        row = ROW;
        bool headmade = false;

        for (int i = 0; i < inSize; i++) {
                if (mtx[i]) {
                    if (!headmade) {
                        Head->val = mtx[i];
                        Head->idx = i;
                        Head->next = Crnt;
                        headmade = true;
                        Crnt = Head;
                    }
                    else {
                        VListnp p = new VNode;
                        p->val = mtx[i];
                        p->next = NULL;
                        Crnt->next = p;
                        Crnt = p;
                    }
                }
            }
        }

    void print() override {
        VListnp crnt = Head;
        bool fin = false;
        for (int i = 0; i < size; i++) {
                if (i == crnt->idx && !fin) {
                    cout << crnt->val << " ";
                    if (crnt->next == NULL)fin = true;
                    else crnt = crnt->next;
                }
                else cout << "0 ";
            }
            cout << endl;
        crnt = NULL;
        delete crnt;
    }

    VListnp Valsearch( double check) {
        if (!check) {
            cout << "Does not work for 0" << endl;
            return NULL;
        }
        VListnp crnt = Head;
        while (crnt) {
            if (crnt->val == check)return crnt;
            else crnt = crnt->next;
        }
        return NULL;
    }

    VListnp INDsearch( int IDX) {
        VListnp crnt = Head;
        if (size <= IDX) {
            cout << "WRONG INPUT " << endl;
            return 0;
        }
        while (crnt) {
            if (crnt->idx == IDX)return crnt;
            if (crnt->idx > IDX)return NULL;
            else crnt = crnt->next;
        }
        cout << endl;
        return NULL;
    }

};


class ArrMatrix : public MatrixBase {
private:
    ELM* arr;
    int size;
    int ACTsize;
public:

    ArrMatrix(int inSize, double** mtx) : size(inSize) {
        ACTsize = inSize;
        for (int i = 0; i < inSize; i++) {
            for (int j = 0; j < inSize; j++) {
                if (mtx[i][j])size++;
            }
        }

        arr = new ELM[size];

        int crnt = 0;

        for (int i = 0; i < inSize; i++) {
            for (int j = 0; j < inSize; j++) {
                if (mtx[i][j]) {
                    arr[crnt].val = mtx[i][j];
                    arr[crnt].row = i;
                    arr[crnt].clmn = j;
                    crnt++;
                }
            }
        }
    }

    void print() override{
        int crnt=0;
        for (int i = 0; i < ACTsize; i++) {
            cout << endl;
            for (int j = 0; j < ACTsize; j++) {
                if (arr[crnt].row == i && arr[crnt].clmn == j) {
                    cout << arr[crnt].val << " ";
                    crnt++;
                }
                else cout << "0 ";
            }
        }
    }

    ELM ValSearch(double check) {
        ELM k;
        if (!check) {
            cout << "Does not work for 0" << endl;
            return k;
        }
        for (int i = 0; i < size; i++) {
            if (arr[i].val == check)return arr[i];
        }
        return k;
    }

     ELM IndSearch(double ROW, double CLMN) {
        ELM k;
        if (ROW >= size || CLMN >= size) {
            cout << "WRONG INPUT" << endl;
            return k;
        }
        for (int i = 0; i < size; i++) {
            if (arr[i].row == ROW && arr[i].clmn == CLMN)return arr[i];
        }
        k.clmn = CLMN;
        k.row = ROW;
        k.val = 0;
        return k;
    }
};

class ArrVector : public MatrixBase {
private:
    ELV* arr;
    bool row;
    int size;
    int ACTsize;
public:

    ArrVector(int inSize, double* mtx, bool ROW) : size(inSize) {
        ACTsize = inSize;
        row = ROW;
        for (int i = 0; i < inSize; i++) {
                if (mtx[i])size++;
        }

        arr = new ELV[size];
        int crnt = 0;

        for (int i = 0; i < inSize; i++) {
                if (mtx[i]) {
                    arr[crnt].val = mtx[i];
                    arr[crnt].idx = i;
                    crnt++;
                }
        }
    }

    void print() override {
        int crnt = 0;
        cout << endl;
        for (int i = 0; i < ACTsize; i++) {
            if (arr[crnt].idx == i) {
                cout << arr[crnt].val << " ";
                crnt++;
            }
            else cout << "0 ";
        }
    }

    ELV ValSearch(double check) {
        ELV k;
        for (int i = 0; i < size; i++) {
            if (arr[i].val == check)return arr[i];
        }
        return k;
    }

    ELV IndSearch(double IDX) {
        ELV k;
        for (int i = 0; i < size; i++) {
            if (arr[i].idx == IDX)return arr[i];
        }
        return k;
    }

};


int main() {
    int OPT = 1;

    while (OPT) {

        cout << "<<<<<<<<<<<<<<<<<OPTIONS>>>>>>>>>>>>>>>>>>>" << endl << endl;
        cout << "1.To Check points operations" << endl;
        cout << "2.To Check Lines/segments operations" << endl;
        cout << "3.To Check Triangle operations" << endl;
        cout << "4.To Check Rectangle operations" << endl;
        cout << "5.To Check Circle operations" << endl;
        cout << "6.To Check Matrix operations" << endl;
        cout << "7.To Check Vector operations" << endl;
        cout << "0.To exit" << endl << endl;

        cin >> OPT;

        switch (OPT) {//partially written by Chatgpt, adjusted by me
        case 0:
            return 0;
            break;

        case 1: {
            Point A(0, 0), B(0, 0), C(0, 0);
            A = A.GEN();
            B = B.GEN();
            C = C.GEN();
            cout << "Points generated:\n";
            A.printInfo();
            B.printInfo();
            C.printInfo();
            cout << (Point::isOnLine(A, B, C) ? "Points are on a common line\n" : "Points are not on a common line\n");
            int x, y;
            x = dis(gen) * (rand() % 20);
            y = dis(gen) * (rand() % 20);
            cout << "shif cords are: ( " << x << ", " << y << " )\n";
            A.shift(x, y);
            cout << "After shift:\n";
            A.printInfo();

            break;
        }

        case 2: {
            Line line1(Point::GEN(), Point::GEN()), line2(Point::GEN(), Point::GEN());
            cout << "Line 1:\n";
            line1.printInfo();
            cout << "\nLine 2:\n";
            line2.printInfo();
            cout << (Line::isParalel(line1, line2) ? "Lines are parallel\n" : "Lines are not parallel\n");
            cout << "Angle between lines: " << Line::angle(line1, line2) << endl;
            if (!Line::isParalel(line1, line2)) {
                Point intersection = Line::crossing(line1, line2);
                cout << "Intersection point:\n";
                intersection.printInfo();
            }
            else {
                cout << "Lines are parallel; no intersection point.\n";
            }
            cout << "////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
            break;
        }

        case 3: {
            Triangle tri1(Point::GEN(), Point::GEN(), Point::GEN());
            Triangle tri2(Point::GEN(), Point::GEN(), Point::GEN());
            cout << "Triangle 1:\n";
            tri1.printInfo();
            cout << "Triangle area: " << Triangle::area(tri1) << endl;
            cout << "Triangle perimeter: " << Triangle::perimeter(tri1) << endl;
            cout << "\nTriangle 2:\n";
            tri2.printInfo();
            cout << "Triangle area: " << Triangle::area(tri2) << endl;
            cout << "Triangle perimeter: " << Triangle::perimeter(tri2) << endl;
            Point circumcenter(0, 0);
            circumcenter = Triangle::outcircle(tri1);
            cout << "\nCircumcenter (Outcircle center) of Triangle 1:\n";
            circumcenter.printInfo();
            Point incircleCenter(0, 0);
            incircleCenter = Triangle::incircle(tri1);
            cout << "Incircle center of Triangle 1:\n";
            incircleCenter.printInfo();
            cout << "\nChecking similarity between Triangle 1 and Triangle 2:\n";
            if (Triangle::issimilar(tri1, tri2)) {
                cout << "Triangle 1 and Triangle 2 are similar.\n";
            }
            else {
                cout << "Triangle 1 and Triangle 2 are not similar.\n";
            }
            int x, y;
            x = dis(gen) * (rand() % 20);
            y = dis(gen) * (rand() % 20);
            cout << "shif cords are: ( " << x << ", " << y << " )\n";
            tri1.shift(x, y);
            cout << "After shifting Triangle 1:\n";
            tri1.printInfo();
            cout << "////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
            break;
        }

        case 4: {
            Rectangle rect(Point::GEN(), Point::GEN(), Point::GEN(), Point::GEN());
            rect.printInfo();
            cout << "Rectangle perimeter: " << Rectangle::perimeter(rect) << endl;
            if (Rectangle::isconvex(rect)) {
                cout << "Rectangle is convex " << endl;
                cout << "Rectangle area: " << Rectangle::area(rect) << endl;
            }
            else cout << "rectangle is not convex" << endl;
            int x, y;
            x = dis(gen) * (rand() % 20);
            y = dis(gen) * (rand() % 20);
            cout << "shif cords are: ( " << x << ", " << y << " )\n";
            rect.shift(x, y);
            cout << "After shift:\n";
            rect.printInfo();
            cout << "////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
            break;
        }

        case 5: {
            Circle circle(Point::GEN(), dis(gen) * 10);
            circle.printInfo();
            cout << "Circle area: " << Circle::area(circle) << endl;
            cout << "Circle perimeter: " << Circle::perimeter(circle) << endl;
            int x, y;
            x = dis(gen) * (rand() % 20);
            y = dis(gen) * (rand() % 20);
            cout << "shif cords are: ( " << x << ", " << y << " )\n";
            circle.shift(x,y);
            cout << "After shift:\n";
            circle.printInfo();
            cout << "////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
            break;
        }

        case 6: {
            int size = rand() % 10 + 2;
            double** matA = MATGEN(size);
            double** matB = MATGEN(size);
            ListMatrix listMatrixA(size, matA);
            ListMatrix listMatrixB(size, matB);
            cout << "ListMatrix A:\n";
            listMatrixA.print();
            cout << "\n";
            cout << "\nListMatrix B:\n";
            listMatrixB.print();
            cout << "\n";
            cout << "\nSum of ListMatrix A and B:\n";
            ListMatrix::Summ(listMatrixA, listMatrixB).print();
            cout << "\n";
            size_t listMatrixMemory = sizeof(ListMatrix) + sizeof(MNode) * size * size;
            cout << "\nMemory used by ListMatrix A: " << listMatrixMemory << " bytes\n";
            ArrMatrix arrMatrixA(size, matA);
            ArrMatrix arrMatrixB(size, matB);
            cout << "\nArrMatrix A:\n";
            arrMatrixA.print();
            cout << "\n";
            cout << "\nArrMatrix B:\n";
            arrMatrixB.print();
            cout << "\n";
            size_t arrMatrixMemory = sizeof(ArrMatrix) + sizeof(ELM) * size * size;
            cout << "\nMemory used by ArrMatrix A: " << arrMatrixMemory << " bytes\n";
            double searchVal = dis(gen) * 50;
            cout << "\nSearching for value " << searchVal << " in ListMatrix A:\n";
            MListnp listResult = listMatrixA.Valsearch(searchVal);
            if (listResult)
                cout << "Value found at (" << listResult->row << ", " << listResult->clmn << ")\n";
            else
                cout << "Value not found.\n";
            cout << "\nSearching for value " << searchVal << " in ArrMatrix A:\n";
            ELM arrResult = arrMatrixA.ValSearch(searchVal);
            if (arrResult.row >= 0)
                cout << "Value found at (" << arrResult.row << ", " << arrResult.clmn << ")\n";
            else
                cout << "Value not found.\n";
            int rowIndex = rand() % size;
            int colIndex = rand() % size;
            cout << "\nSearching for element at index (" << rowIndex << ", " << colIndex << ") in ListMatrix A:\n";
            listResult = listMatrixA.INDsearch(rowIndex, colIndex);
            if (listResult)
                cout << "Element found with value: " << listResult->val << endl;
            else
                cout << "Element not found.\n";
            cout << "\nSearching for element at index (" << rowIndex << ", " << colIndex << ") in ArrMatrix A:\n";
            arrResult = arrMatrixA.IndSearch(rowIndex, colIndex);
            if (arrResult.row >= 0)
                cout << "Element found with value: " << arrResult.val << endl;
            else
                cout << "Element not found.\n";
            cout << "////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
            break;
        }

        case 7: {
            int size = rand() % 10 + 2;
            double* vecA = VECGEN(size);
            double* vecB = VECGEN(size);
            ListVector listVectorA(size, vecA, true);
            ListVector listVectorB(size, vecB, true);
            cout << "ListVector A:\n";
            listVectorA.print();
            cout << "\n";
            cout << "\nListVector B:\n";
            listVectorB.print();
            cout << "\n";
            size_t listVectorMemory = sizeof(ListVector) + sizeof(VNode) * size;
            cout << "\nMemory used by ListVector A: " << listVectorMemory << " bytes\n";
            ArrVector arrVectorA(size, vecA, true);
            ArrVector arrVectorB(size, vecB, true);
            cout << "\nArrVector A:\n";
            arrVectorA.print();
            cout << "\n";
            cout << "\nArrVector B:\n";
            arrVectorB.print();
            cout << "\n";
            size_t arrVectorMemory = sizeof(ArrVector) + sizeof(ELV) * size;
            cout << "\nMemory used by ArrVector A: " << arrVectorMemory << " bytes\n";
            double searchVal = dis(gen) * 50;
            cout << "\nSearching for value " << searchVal << " in ListVector A:\n";
            VListnp listVResult = listVectorA.Valsearch(searchVal);
            if (listVResult)
                cout << "Value found at index " << listVResult->idx << endl;
            else
                cout << "Value not found.\n";
            cout << "\nSearching for value " << searchVal << " in ArrVector A:\n";
            ELV arrVResult = arrVectorA.ValSearch(searchVal);
            if (arrVResult.idx >= 0)
                cout << "Value found at index " << arrVResult.idx << endl;
            else
                cout << "Value not found.\n";
            int searchIdx = rand() % size;
            cout << "\nSearching for element at index " << searchIdx << " in ListVector A:\n";
            listVResult = listVectorA.INDsearch(searchIdx);
            if (listVResult)
                cout << "Element found with value: " << listVResult->val << endl;
            else
                cout << "Element not found.\n";
            cout << "\nSearching for element at index " << searchIdx << " in ArrVector A:\n";
            arrVResult = arrVectorA.IndSearch(searchIdx);
            if (arrVResult.idx >= 0)
                cout << "Element found with value: " << arrVResult.val << endl;
            else
                cout << "Element not found.\n";
            cout << "////////////////////////////////////////////////////////////////////////////////////" << endl << endl;
            break;
        }
        }
    }

    return 0;
}