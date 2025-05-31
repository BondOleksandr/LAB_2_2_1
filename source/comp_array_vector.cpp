#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "RNG.hpp"
#include "all_matrix&vector.hpp"

using namespace std;

struct Element_Vector {
    double val=0;
    int index=-1;
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