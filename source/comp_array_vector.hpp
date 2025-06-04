#pragma once

#include "array_realization.hpp"

/**
 * @struct Element_Vector
 * @brief Represents a non-zero element in a sparse vector.
 */
struct Element_Vector {
    double val = 0;  ///< Value of the vector element
    int index = -1;  ///< Index of the element
};

/**
 * @class ArrVector
 * @brief Array-based realization of a sparse vector.
 */
class ArrVector : public ArrayRealization {
private:
    Element_Vector* arr; ///< Array storing non-zero elements
    bool row;            ///< Indicates if vector is a row (true) or column (false)
    int size;            ///< Total size of the vector
    int ACTsize;         ///< Actual number of non-zero elements

public:
    /**
     * @brief Constructs a sparse vector from a dense array.
     * @param inSize Size of the vector.
     * @param vector Pointer to the dense array.
     * @param ROW True if the vector is a row vector, false if column vector.
     */
    ArrVector(int inSize, double* vector, bool ROW);

    /// @brief Prints the stored vector elements.
    void print() override;

    /**
     * @brief Searches for an element with the given value.
     * @param check Value to search for.
     * @return Element_Vector with value and index, or default if not found.
     */
    Element_Vector ValSearch(double check);

    /**
     * @brief Searches for an element by index.
     * @param IDX Index to search for.
     * @return Element_Vector at the given index, or default if not found.
     */
    Element_Vector IndSearch(double IDX);
};
