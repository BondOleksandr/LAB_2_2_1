#pragma once
#include <iostream>
#include "RNG.hpp"
#include "list_realization.hpp"

typedef struct Matrix_Node {
    double val;
    int row;
    int clmn;
    Matrix_Node* next;
} MListn, *Matrix_Listnp;

class ListMatrix : public ListRealization {
private:
    Matrix_Listnp Head;
    int size;

public:
    ListMatrix(int inSize, double** matrix);
    void print() override;
    Matrix_Listnp Valsearch(double check);                    // Returns node with specified value
    Matrix_Listnp INDsearch(int ROW, int CLMN);               // Returns node at (ROW, CLMN) or zero-node
    static ListMatrix Summ(ListMatrix A, ListMatrix B);       // Returns sum of two sparse matrices
    void xScalar(ListMatrix A, int x);                        // In-place scalar multiplication
};