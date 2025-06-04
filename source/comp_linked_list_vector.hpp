#pragma once
#include <iostream>
#include "RNG.hpp"
#include "list_realization.hpp"

/**
 * @struct Vector_Node
 * @brief Represents a node in a singly linked list for a sparse vector element.
 */
typedef struct Vector_Node {
    double val;             ///< Value of the vector element
    int index;              ///< Index of the element
    Vector_Node* next;      ///< Pointer to the next element
} VListn, *Vector_Listnp;

/**
 * @class ListVector
 * @brief Linked list-based realization of a sparse vector.
 */
class ListVector : public ListRealization {
private:
    Vector_Listnp Head; ///< Pointer to the head of the list
    int size;           ///< Size of the vector
    bool row;           ///< True if row vector, false if column vector

public:
    /**
     * @brief Constructs a sparse vector from a dense array.
     * @param inSize Size of the vector.
     * @param vector Pointer to the dense array.
     * @param ROW True if the vector is a row vector, false if column vector.
     */
    ListVector(int inSize, double* vector, bool ROW);

    /// @brief Prints the stored vector elements.
    void print() override;

    /**
     * @brief Searches for a node with the specified value.
     * 
     * Only non-zero elements are stored and searchable.
     * 
     * @param check Value to search for.
     * @return Pointer to the node with the given value, or nullptr if not found.
     */
    Vector_Listnp Valsearch(double check);

    /**
     * @brief Searches for a node at a given index.
     * @param IDX Index to search for.
     * @return Pointer to the node at the given index, or nullptr if not found.
     */
    Vector_Listnp INDsearch(int IDX);
};
