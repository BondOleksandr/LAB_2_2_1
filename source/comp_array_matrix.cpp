#include "comp_array_matrix.hpp"
#include <iostream>

ArrMatrix::ArrMatrix(int inSize, double** matrix) : size(inSize) {
    ACTsize = inSize;
    for (int i = 0; i < inSize; i++) {
        for (int j = 0; j < inSize; j++) {
            if (matrix[i][j]) size++;
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


void ArrMatrix::print() {
    int crnt = 0;
    for (int i = 0; i < ACTsize; i++) {
        std::cout << std::endl;
        for (int j = 0; j < ACTsize; j++) {
            if (arr[crnt].row == i && arr[crnt].clmn == j) {
                std::cout << arr[crnt].val << " ";
                crnt++;
            } else {
                std::cout << "0 ";
            }
        }
    }
}

Element_Matrix ArrMatrix::ValSearch(double check) {
    Element_Matrix result;
    if (!check) {
        std::cout << "Does not work for 0" << std::endl;
        return result;
    }
    for (int i = 0; i < size; i++) {
        if (arr[i].val == check) return arr[i];
    }
    return result;
}

Element_Matrix ArrMatrix::IndSearch(double ROW, double CLMN) {
    Element_Matrix result;
    if (ROW >= size || CLMN >= size) {
        std::cout << "WRONG INPUT" << std::endl;
        return result;
    }
    for (int i = 0; i < size; i++) {
        if (arr[i].row == ROW && arr[i].clmn == CLMN) return arr[i];
    }
    result.clmn = CLMN;
    result.row = ROW;
    result.val = 0;
    return result;
}
