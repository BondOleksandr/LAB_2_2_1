#pragma once

#include <iostream>
#include "array_realization.hpp"

struct Element_Matrix {
    double val = 0;
    int row = -1;
    int clmn = -1;
};

class ArrMatrix : public ArrayRealization {
private:
    Element_Matrix* arr;
    int size;
    int ACTsize;

public:
    ArrMatrix(int inSize, double** matrix);

    void print() override;
    Element_Matrix ValSearch(double check);
    Element_Matrix IndSearch(double ROW, double CLMN);
};
