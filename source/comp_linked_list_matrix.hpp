#pragma once
#include <iostream>
#include "RNG.hpp"
#include "all_matrix&vector.hpp"

typedef struct Matrix_Node {
    double val;
    int row;
    int clmn;
    Matrix_Node* next;
} MListn, *Matrix_Listnp;

class ListMatrix : public MatrixBase {
private:
    Matrix_Listnp Head;
    int size;

public:
    ListMatrix(int inSize, double** matrix);
    void print() override;
    Matrix_Listnp Valsearch(double check);
    Matrix_Listnp INDsearch(int ROW, int CLMN);               // Returns node at (ROW, CLMN) or zero-node
    static ListMatrix Summ(ListMatrix A, ListMatrix B);       // Returns sum of two sparse matrices
    void xScalar(ListMatrix A, int x);                        // In-place scalar multiplication
};