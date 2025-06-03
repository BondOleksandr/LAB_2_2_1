#pragma once

#include "array_realization.hpp"

struct Element_Vector {
    double val = 0;
    int index = -1;
};

class ArrVector : public ArrayRealization{
private:
    Element_Vector* arr;
    bool row;
    int size;
    int ACTsize;

public:
    ArrVector(int inSize, double* vector, bool ROW);

    void print() override;
    Element_Vector ValSearch(double check);
    Element_Vector IndSearch(double IDX);
};
