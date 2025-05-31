#pragma once
#include <iostream>
#include <vector>
#include <cmath>
#include "RNG.hpp"
#include "all_matrix&vector.hpp"


struct Element_Matrix{
    double val = 0;
    int row=-1;
    int clmn=-1;
};

using namespace std;

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