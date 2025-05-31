#pragma once
#include "comp_linked_list_matrix.hpp"

class MatrixBase {
public:
    virtual void print() = 0;
    virtual ~MatrixBase() = default;
};