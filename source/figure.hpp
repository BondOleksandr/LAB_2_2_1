#pragma once
#include <iostream>
using namespace std;

class Figure {
public:
    virtual void printInfo() const = 0;               // Prints figure info
    virtual void shift(double dx, double dy) = 0;     // Applies shift to figure
    virtual ~Figure() = default;

    template <typename PrI>
    void printFigureInfo(const PrI& figure);          // Prints info using CRTP-like templated method
};
