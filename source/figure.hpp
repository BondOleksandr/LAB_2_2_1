#pragma once
#include <iostream>
using namespace std;

/**
 * @class Figure
 * @brief Abstract base class for geometric figures.
 */
class Figure {
public:
    /**
     * @brief Prints information about the figure.
     * 
     * Must be implemented by derived classes.
     */
    virtual void printInfo() const = 0;

    /**
     * @brief Applies a shift to the figure by dx and dy.
     * 
     * Must be implemented by derived classes.
     * 
     * @param dx Shift along X axis.
     * @param dy Shift along Y axis.
     */
    virtual void shift(double dx, double dy) = 0;

    /// @brief Virtual destructor for safe polymorphic destruction.
    virtual ~Figure() = default;

    /**
     * @brief Prints figure info using CRTP-like templated method.
     * 
     * Useful for templated base class to call derived methods without RTTI.
     * 
     * @tparam PrI Type that implements printInfo().
     * @param figure Object of type PrI.
     */
    template <typename PrI>
    void printFigureInfo(const PrI& figure);
};
