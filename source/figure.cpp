#include "figure.hpp"

template <typename PrI>
void Figure::printFigureInfo(const PrI& figure) {
    static_assert(std::is_base_of<Figure, PrI>::value, "T must derive from Figure");
    figure.printInfo();
}

