#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "RNG.hpp"
#include "all_matrix&vector.hpp"

typedef struct Vector_Node {
    double val;
    int index;
    Vector_Node* next;
}VListn, * Vector_Listnp;

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