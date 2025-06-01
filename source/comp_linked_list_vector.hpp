#pragma once
#include <iostream>
#include "RNG.hpp"
#include "all_matrix&vector.hpp"

typedef struct Vector_Node {
    double val;
    int index;
    Vector_Node* next;
} VListn, *Vector_Listnp;

class ListVector : public MatrixBase {
private:
    Vector_Listnp Head;
    int size;
    bool row;

public:
    ListVector(int inSize, double* vector, bool ROW);
    void print() override;
    Vector_Listnp Valsearch(double check);                   // Returns pointer to node with given value (non-zero only)
    Vector_Listnp INDsearch(int IDX);                        // Returns pointer to node with given index or NULL
};