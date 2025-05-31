#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "RNG.hpp"

using namespace std;

typedef struct Matrix_Node {
    double val;
    int row;
    int clmn;
    Matrix_Node* next;
}MListn, * Matrix_Listnp;

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