#include <iostream>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

random_device rd;  
mt19937 gen(rd()); 
uniform_real_distribution<> dis(0.0, 1.0);

struct Element_Matrix{
    double val = 0;
    int row=-1;
    int clmn=-1;
};

struct Element_Vector {
    double val=0;
    int index=-1;
};

typedef struct Matrix_Node {
    double val;
    int row;
    int clmn;
    Matrix_Node* next;
}MListn, * Matrix_Listnp;

typedef struct Vector_Node {
    double val;
    int index;
    Vector_Node* next;
}VListn, * Vector_Listnp;

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

    static bool isOnLine(const Point& a, const Point& b, const Point& c) {// Returns 1 if 3 points are on 1 line, else 0
        return ((c.getX() - a.getX()) * (b.getY() - a.getY())) == ((c.getY() - a.getY()) * (b.getX() - a.getX()));
    }
};

class Line {
private:
    Point BEG;
    Point END;

public:
    Line(const Point& a, const Point& b) : BEG(a), END(b) {}

    Point getPointBEG() const { return BEG; }
    Point getPointEND() const { return END; }

    void printInfo() const {
        cout << "Line defined by points: " << endl;
        BEG.printInfo();
        END.printInfo();
    }

    static Line GEN() {
        Point beg = beg.GEN();
        Point end = end.GEN();
        Line C(beg, end);
        return C;
    }

    static bool isParalel(const Line& z, Line& u) {//Returns 1, if lines are parallel, else 0
        return(((z.END.getX() - z.BEG.getX()) / (z.END.getY() - z.BEG.getY())) == ((u.END.getX() - u.BEG.getX()) / (u.END.getY() - u.BEG.getY())));
    }

    static Point crossing(const Line& z, Line& u) {//point of the crossing of 2 lines
        Point Crossing_point(0, 0);
        if (isParalel(z, u)) {
            Crossing_point.setX(14);
            Crossing_point.setY(88);
        }
        else {
            double c1 = (z.END.getY() - z.BEG.getY()) / (z.END.getX() - z.BEG.getX());
            double c2 = (u.END.getY() - u.BEG.getY()) / (u.END.getX() - u.BEG.getX());
            Crossing_point.setX((u.BEG.getY() - z.END.getY() + z.BEG.getX() * c1 - u.BEG.getX() * c2) / (c1 - c2));
            Crossing_point.setY(((Crossing_point.getX() - z.BEG.getX()) * c1) + z.BEG.getY());
        }
        return Crossing_point;
    }

    static double angle(const Line& z, Line& u) {//As angle between vectors, that are designated by the 2 points of the line
        double ax = z.END.getX() - z.BEG.getX();
        double ay = z.END.getY() - z.BEG.getY();
        double bx = u.END.getX() - u.BEG.getX();
        double by = u.END.getY() - u.BEG.getY();
        return acos((ax * bx + ay * by) / (sqrt(ax * ax + ay * ay) * sqrt(bx * bx + by * by)));
    }

    static double LLength(const Line& z) {//Lenght of vector between 2 defining points
        double ax = z.END.getX() - z.BEG.getX();
        double ay = z.END.getY() - z.BEG.getY();
        return sqrt(ax * ax + ay * ay);
    }
};

class Figure {
public:

    virtual void printInfo() const = 0;//polimorph 2 static

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

class Circle : public Figure {
private:
    Point center;
    double r;
public:
    Circle(const Point& cent, const double r) : center(center), r(r) {}

    Point getO() const { return center; }
    double getR() const { return r; }

    void setO(Point newCenter) { center = newCenter; }
    void setR(double newR) { r = newR; }

    void shift(double dx, double dy) override {
        center.shift(dx, dy);
    }

    void printInfo() const override {
        cout << "Circle with center: " << endl;
        center.printInfo();
        cout << "and radius " << r << endl;
    }

    static double area(const Circle& CL) {//area of circle
        return (CL.r) * (CL.r) * 3.141592;
    }

    static double perimeter(const Circle& CL) {//perimeter of circle
        return 2 * (CL.r) * 3.141592;
    }

    static Circle GEN() {
        Point O = O.GEN();
        double rad = (dis(gen) * (rand() % 100));
        Circle OOO(O, rad);
        return OOO;
    }

};

template <typename PrI>//out-method for figures
void printFigureInfo(const PrI& figure) {
    static_assert(is_base_of<Figure, PrI>::value, "T must derive from Figure");
    figure.printInfo();
}

/////////////////////////////////////////////////////////////////MATRIX PART//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

double** MATGEN(int size) {//generates double type matrix
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

double* VECGEN(int size) {//generates double type vector
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

    Matrix_Listnp Head;
    int size;

public:

    ListMatrix(int inSize, double** matrix) : size(inSize), Head(nullptr) {//Turns 2d array, that represents matrix, into compressed linked list with same purpose
        Head = new Matrix_Node;
        Matrix_Listnp Crnt = NULL;
        bool headmade = false;
        size = inSize;
        Head->val = 0;
        Head->next = NULL;
        Head->row = 0;
        Head->clmn = 0;

        for (int i = 0; i < inSize; i++) {
            for (int j = 0; j < inSize; j++) {
                if (matrix[i][j]) {
                    if (!headmade) {
                        Head->val = matrix[i][j];
                        Head->row = i;
                        Head->clmn = j;
                        Head->next = Crnt;
                        headmade = true;
                        Crnt = Head;
                    }
                    else {
                        Matrix_Listnp p = new Matrix_Node;
                        p->val = matrix[i][j];
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
        Matrix_Listnp crnt = Head;
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

    Matrix_Listnp Valsearch( double check) {//search by value
        if (!check) {
            cout << "Does not work for 0" << endl;
            return NULL;
        }
        Matrix_Listnp crnt = Head;
        while (crnt) {
            if (crnt->val == check)return crnt;
            else crnt = crnt->next;
        }
        return NULL;
    }

    Matrix_Listnp INDsearch(int ROW, int CLMN) {//search by index
        if (ROW >= size || CLMN >= size) {
            cout << "WRONG INPUT" << endl;
            return NULL;
        }
        Matrix_Listnp crnt = Head;
        while (crnt) {
            if (crnt->row == ROW && crnt->clmn == CLMN)return crnt;
            if (crnt->row >= ROW && crnt->clmn >= CLMN) {
                crnt = new Matrix_Node;
                crnt->val = 0;
                crnt->row = ROW;
                crnt->clmn = CLMN;
                return crnt;
            }
            else crnt = crnt->next;
        }
        crnt = new Matrix_Node;
        crnt->val = 0;
        crnt->row = ROW;
        crnt->clmn = CLMN;
        return crnt;
    }
    
    static ListMatrix Summ(ListMatrix A, ListMatrix B) {//sums matrixes, represented by comp. Linked list
        if (!A.Head->val)return B;
        if (!B.Head->val)return A;
        ListMatrix RESULT(0, 0);
        Matrix_Listnp Ccrnt = new Matrix_Node;
        Matrix_Listnp Acrnt = A.Head;
        Matrix_Listnp Bcrnt = B.Head;
        RESULT.Head = new Matrix_Node;
        RESULT.size = A.size;

        if (A.Head->row > B.Head->row) {
            RESULT.Head->val = B.Head->val;
            RESULT.Head->row = B.Head->row;
            RESULT.Head->clmn = B.Head->clmn;
            RESULT.Head->next = NULL;
            Bcrnt = B.Head->next;
        }
        else {
            if (A.Head->row == B.Head->row) {
                if (RESULT.Head->clmn > B.Head->clmn) {
                    RESULT.Head->val = B.Head->val;
                    RESULT.Head->row = B.Head->row;
                    RESULT.Head->clmn = B.Head->clmn;
                    RESULT.Head->next = NULL;
                    Bcrnt = B.Head->next;
                }
                if (A.Head->clmn == B.Head->clmn) {
                    RESULT.Head->val = B.Head->val+A.Head->val;
                    RESULT.Head->row = B.Head->row;
                    RESULT.Head->clmn = B.Head->clmn;
                    RESULT.Head->next = NULL;
                    Bcrnt = B.Head->next;
                    Acrnt = A.Head->next;
                }
                else {
                    RESULT.Head->val = A.Head->val;
                    RESULT.Head->row = A.Head->row;
                    RESULT.Head->clmn = A.Head->clmn;
                    RESULT.Head->next = NULL;
                    Acrnt = A.Head->next;
                }
            }
            else
            {
                RESULT.Head->val = A.Head->val;
                RESULT.Head->row = A.Head->row;
                RESULT.Head->clmn = A.Head->clmn;
                RESULT.Head->next = NULL;
                Acrnt = A.Head->next;
            }
        }
        Ccrnt = RESULT.Head;
        if (Acrnt && Bcrnt) {
            while ((Acrnt && Bcrnt) && Acrnt->row < Bcrnt->row) {
                Matrix_Listnp p = new Matrix_Node;
                p->val = Acrnt->val;
                p->row = Acrnt->row;
                p->clmn = Acrnt->clmn;
                p->next = NULL;
                Ccrnt->next = p;
                Ccrnt = p;
                Acrnt = Acrnt->next;
            }

            while ((Acrnt && Bcrnt) && Acrnt->row > Bcrnt->row) {
                Matrix_Listnp p = new Matrix_Node;
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
                    Matrix_Listnp p = new Matrix_Node;
                    p->val = Bcrnt->val;
                    p->row = Bcrnt->row;
                    p->clmn = Bcrnt->clmn;
                    p->next = NULL;
                    Ccrnt->next = p;
                    Ccrnt = p;
                    Bcrnt = Bcrnt->next;
                }

                while ((Acrnt && Bcrnt) && Acrnt->clmn < Bcrnt->clmn) {
                    Matrix_Listnp p = new Matrix_Node;
                    p->val = Acrnt->val;
                    p->row = Acrnt->row;
                    p->clmn = Acrnt->clmn;
                    p->next = NULL;
                    Ccrnt->next = p;
                    Ccrnt = p;
                    Acrnt = Acrnt->next;
                }

                while ((Acrnt && Bcrnt) && Acrnt->clmn > Bcrnt->clmn) {
                    Matrix_Listnp p = new Matrix_Node;
                    p->val = Bcrnt->val;
                    p->row = Bcrnt->row;
                    p->clmn = Bcrnt->clmn;
                    p->next = NULL;
                    Ccrnt->next = p;
                    Ccrnt = p;
                    Bcrnt = Bcrnt->next;
                }

                while ((Acrnt && Bcrnt) && Acrnt->clmn == Bcrnt->clmn) {
                    Matrix_Listnp p = new Matrix_Node;
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
            Matrix_Listnp p = new Matrix_Node;
            p->val = Acrnt->val;
            p->row = Acrnt->row;
            p->clmn = Acrnt->clmn;
            p->next = NULL;
            Ccrnt->next = p;
            Ccrnt = p;
            Acrnt = Acrnt->next;
        }
        while (Bcrnt) {
            Matrix_Listnp p = new Matrix_Node;
            p->val = Bcrnt->val;
            p->row = Bcrnt->row;
            p->clmn = Bcrnt->clmn;
            p->next = NULL;
            Ccrnt->next = p;
            Ccrnt = p;
            Bcrnt = Bcrnt->next;
        }
        return RESULT;
    }

    void xScalar(ListMatrix A, int x) {//multiplies matrix by scalar
        ListMatrix B(0, 0);
        Matrix_Listnp crnt = A.Head;
        while (crnt) {
            crnt->val *= x;
            crnt->next;
        }
    }

};

class ListVector : public MatrixBase {//why inside matrix class?
private:

    Vector_Listnp Head;
    int size;
    bool row;

public:

    ListVector(int inSize, double* vector, bool ROW) : size(inSize), Head(nullptr) {
        Head = new Vector_Node;
        Vector_Listnp Crnt = Head;
        size = inSize;
        Head->next = NULL;
        Head->index = 0;
        Head->val = 0;
        row = ROW;
        bool headmade = false;

        for (int i = 0; i < inSize; i++) {//turns 1d array representing vector into compressed linked list
                if (vector[i]) {
                    if (!headmade) {
                        Head->val = vector[i];
                        Head->index = i;
                        Head->next = Crnt;
                        headmade = true;
                        Crnt = Head;
                    }
                    else {
                        Vector_Listnp p = new Vector_Node;
                        p->val = vector[i];
                        p->next = NULL;
                        Crnt->next = p;
                        Crnt = p;
                    }
                }
            }
        }

    void print() override {
        Vector_Listnp crnt = Head;
        bool fin = false;
        for (int i = 0; i < size; i++) {
                if (i == crnt->index && !fin) {
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

    Vector_Listnp Valsearch( double check) {//value search
        if (!check) {
            cout << "Does not work for 0" << endl;
            return NULL;
        }
        Vector_Listnp crnt = Head;
        while (crnt) {
            if (crnt->val == check)return crnt;
            else crnt = crnt->next;
        }
        return NULL;
    }

    Vector_Listnp INDsearch( int IDX) {//index search
        Vector_Listnp crnt = Head;
        if (size <= IDX) {
            cout << "WRONG INPUT " << endl;
            return 0;
        }
        while (crnt) {
            if (crnt->index == IDX)return crnt;
            if (crnt->index > IDX)return NULL;
            else crnt = crnt->next;
        }
        cout << endl;
        return NULL;
    }

};


class ArrMatrix : public MatrixBase {//Matrix, but represented by 1d array of elements without 0??????
private:
    Element_Matrix* arr;
    int size;
    int ACTsize;
public:

    ArrMatrix(int inSize, double** matrix) : size(inSize) {//2d matrix - to 1d array without 0
        ACTsize = inSize;
        for (int i = 0; i < inSize; i++) {
            for (int j = 0; j < inSize; j++) {
                if (matrix[i][j])size++;
            }
        }

        arr = new Element_Matrix[size];

        int crnt = 0;

        for (int i = 0; i < inSize; i++) {
            for (int j = 0; j < inSize; j++) {
                if (matrix[i][j]) {
                    arr[crnt].val = matrix[i][j];
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

    Element_Matrix ValSearch(double check) {//value search
        Element_Matrix result;
        if (!check) {
            cout << "Does not work for 0" << endl;
            return result;
        }
        for (int i = 0; i < size; i++) {
            if (arr[i].val == check)return arr[i];
        }
        return result;
    }

     Element_Matrix IndSearch(double ROW, double CLMN) {//index search
        Element_Matrix result;
        if (ROW >= size || CLMN >= size) {
            cout << "WRONG INPUT" << endl;
            return result;
        }
        for (int i = 0; i < size; i++) {
            if (arr[i].row == ROW && arr[i].clmn == CLMN)return arr[i];
        }
        result.clmn = CLMN;
        result.row = ROW;
        result.val = 0;
        return result;
    }
};

class ArrVector : public MatrixBase {
private:
    Element_Vector* arr;
    bool row;//what is that?
    int size;
    int ACTsize;
public:

    ArrVector(int inSize, double* vector, bool ROW) : size(inSize) {//1d array to 1d array without 0s
        ACTsize = inSize;
        row = ROW;
        for (int i = 0; i < inSize; i++) {
                if (vector[i])size++;
        }

        arr = new Element_Vector[size];
        int crnt = 0;

        for (int i = 0; i < inSize; i++) {
                if (vector[i]) {
                    arr[crnt].val = vector[i];
                    arr[crnt].index = i;
                    crnt++;
                }
        }
    }

    void print() override {
        int crnt = 0;
        cout << endl;
        for (int i = 0; i < ACTsize; i++) {
            if (arr[crnt].index == i) {
                cout << arr[crnt].val << " ";
                crnt++;
            }
            else cout << "0 ";
        }
    }

    Element_Vector ValSearch(double check) {//value search
        Element_Vector k;
        for (int i = 0; i < size; i++) {
            if (arr[i].val == check)return arr[i];
        }
        return k;
    }

    Element_Vector IndSearch(double IDX) {//index search
        Element_Vector k;
        for (int i = 0; i < size; i++) {
            if (arr[i].index == IDX)return arr[i];
        }
        return k;
    }

};


int main() {
    int OPT = 1;//option selector

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

        case 1: {//Operations on points
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

        case 2: {//Operations on Lines
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

        case 3: {//Operations on triangles
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

        case 4: {//Operations on rectangles
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

        case 5: {//Operations on circles
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

        case 6: {//Operations on matrixes
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
            size_t listMatrixMemory = sizeof(ListMatrix) + sizeof(Matrix_Node) * size * size;
            cout << "\nMemory used by ListMatrix A: " << listMatrixMemory << " bytes\n";
            ArrMatrix arrMatrixA(size, matA);
            ArrMatrix arrMatrixB(size, matB);
            cout << "\nArrMatrix A:\n";
            arrMatrixA.print();
            cout << "\n";
            cout << "\nArrMatrix B:\n";
            arrMatrixB.print();
            cout << "\n";
            size_t arrMatrixMemory = sizeof(ArrMatrix) + sizeof(Element_Matrix) * size * size;
            cout << "\nMemory used by ArrMatrix A: " << arrMatrixMemory << " bytes\n";
            double searchVal = dis(gen) * 50;
            cout << "\nSearching for value " << searchVal << " in ListMatrix A:\n";
            Matrix_Listnp listResult = listMatrixA.Valsearch(searchVal);
            if (listResult)
                cout << "Value found at (" << listResult->row << ", " << listResult->clmn << ")\n";
            else
                cout << "Value not found.\n";
            cout << "\nSearching for value " << searchVal << " in ArrMatrix A:\n";
            Element_Matrix arrResult = arrMatrixA.ValSearch(searchVal);
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

        case 7: {//Operations on vectors
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
            size_t listVectorMemory = sizeof(ListVector) + sizeof(Vector_Node) * size;
            cout << "\nMemory used by ListVector A: " << listVectorMemory << " bytes\n";
            ArrVector arrVectorA(size, vecA, true);
            ArrVector arrVectorB(size, vecB, true);
            cout << "\nArrVector A:\n";
            arrVectorA.print();
            cout << "\n";
            cout << "\nArrVector B:\n";
            arrVectorB.print();
            cout << "\n";
            size_t arrVectorMemory = sizeof(ArrVector) + sizeof(Element_Vector) * size;
            cout << "\nMemory used by ArrVector A: " << arrVectorMemory << " bytes\n";
            double searchVal = dis(gen) * 50;
            cout << "\nSearching for value " << searchVal << " in ListVector A:\n";
            Vector_Listnp listVResult = listVectorA.Valsearch(searchVal);
            if (listVResult)
                cout << "Value found at index " << listVResult->index << endl;
            else
                cout << "Value not found.\n";
            cout << "\nSearching for value " << searchVal << " in ArrVector A:\n";
            Element_Vector arrVResult = arrVectorA.ValSearch(searchVal);
            if (arrVResult.index >= 0)
                cout << "Value found at index " << arrVResult.index<< endl;
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
            if (arrVResult.index >= 0)
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