#pragma once
#include <iostream>
#include "RNG.hpp"
#include "list_realization.hpp"

/**
 * @struct Matrix_Node
 * @brief Represents a node in a singly linked list for a sparse matrix element.
 */
typedef struct Matrix_Node {
    double val;            ///< Value of the matrix element
    int row;               ///< Row index
    int clmn;              ///< Column index
    Matrix_Node* next;     ///< Pointer to the next element in the list
} MListn, *Matrix_Listnp;

/**
 * @class ListMatrix
 * @brief Linked list-based realization of a sparse matrix.
 */
class ListMatrix : public ListRealization {
private:
    Matrix_Listnp Head; ///< Pointer to the head of the linked list
    int size;           ///< Size of the matrix (assumed square: size x size)

public:
    /**
     * @brief Constructs a sparse matrix from a dense 2D array.
     * @param inSize Size of the square matrix.
     * @param matrix Pointer to the 2D array.
     */
    ListMatrix(int inSize, double** matrix);

    /// @brief Prints all non-zero matrix elements.
    void print() override;

    /**
     * @brief Searches for a node with the specified value.
     * @param check Value to search for.
     * @return Pointer to the matching node or nullptr if not found.
     */
    Matrix_Listnp Valsearch(double check);

    /**
     * @brief Searches for a node at the given row and column.
     * @param ROW Row index.
     * @param CLMN Column index.
     * @return Pointer to the node at (ROW, CLMN), or zero-node if not found.
     */
    Matrix_Listnp INDsearch(int ROW, int CLMN);

    /**
     * @brief Returns the sum of two sparse matrices.
     * @param A First matrix.
     * @param B Second matrix.
     * @return New ListMatrix representing the element-wise sum.
     */
    static ListMatrix Summ(ListMatrix A, ListMatrix B);

    /**
     * @brief Performs in-place scalar multiplication of a matrix.
     * @param A Matrix to be multiplied.
     * @param x Scalar multiplier.
     */
    void xScalar(ListMatrix A, int x);
};
