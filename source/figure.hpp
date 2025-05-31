#pragma once

#include <iostream>

using namespace std;

class Figure {
public:

    virtual void printInfo() const = 0;//polimorph 2 static

    virtual void shift(double dx, double dy) = 0;//polimorph 1 dynamic

    virtual ~Figure() = default;

    template <typename PrI>//out-method for figures
    void printFigureInfo(const PrI& figure) {
    static_assert(is_base_of<Figure, PrI>::value, "T must derive from Figure");
    figure.printInfo();
}

};