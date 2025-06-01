#include "comp_array_vector.hpp"
#include <iostream>

ArrVector::ArrVector(int inSize, double* vector, bool ROW) : size(inSize) {
    ACTsize = inSize;
    row = ROW;

    for (int i = 0; i < inSize; i++) {
        if (vector[i]) size++;
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

void ArrVector::print() {
    int crnt = 0;
    std::cout << std::endl;
    for (int i = 0; i < ACTsize; i++) {
        if (arr[crnt].index == i) {
            std::cout << arr[crnt].val << " ";
            crnt++;
        } else {
            std::cout << "0 ";
        }
    }
}

Element_Vector ArrVector::ValSearch(double check) {
    Element_Vector k;
    for (int i = 0; i < size; i++) {
        if (arr[i].val == check) return arr[i];
    }
    return k;
}

Element_Vector ArrVector::IndSearch(double IDX) {
    Element_Vector k;
    for (int i = 0; i < size; i++) {
        if (arr[i].index == IDX) return arr[i];
    }
    return k;
}