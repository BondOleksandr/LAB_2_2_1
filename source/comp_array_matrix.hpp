#pragma once

#include <iostream>
#include "array_realization.hpp"

/**
 * @struct Element_Matrix
 * @brief Represents a non-zero element in a sparse matrix.
 */
struct Element_Matrix {
    double val = 0; ///< Value of the matrix element
    int row = -1;   ///< Row index
    int clmn = -1;  ///< Column index
};

/**
 * @class ArrMatrix
 * @brief Array-based realization of a sparse matrix.
 */
class ArrMatrix : public ArrayRealization {
private:
    Element_Matrix* arr; ///< Array storing non-zero elements
    int size;            ///< Total dimension of the matrix (size x size)
    int ACTsize;         ///< Actual number of non-zero elements

public:
    /**
     * @brief Constructs a sparse matrix from a dense 2D array.
     * @param inSize Size of the square matrix.
     * @param matrix Pointer to 2D array containing matrix data.
     */
    ArrMatrix(int inSize, double** matrix);

    /// @brief Prints the stored matrix elements.
    void print() override;

    /**
     * @brief Searches for an element with the given value.
     * @param check Value to search for.
     * @return Element_Matrix containing value and its position, or default if not found.
     */
    Element_Matrix ValSearch(double check);

    /**
     * @brief Searches for an element at a specific row and column.
     * @param ROW Row index.
     * @param CLMN Column index.
     * @return Element_Matrix at the specified position, or default if not found.
     */
    Element_Matrix IndSearch(double ROW, double CLMN);
};
