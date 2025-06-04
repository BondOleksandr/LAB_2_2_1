#pragma once
#include <iostream>
#include <cmath>
#include "RNG.hpp"

using namespace std;

/**
 * @class Point
 * @brief Represents a point in 2D space with x and y coordinates.
 */
class Point {
private:
    double x; ///< X coordinate
    double y; ///< Y coordinate

public:
    /**
     * @brief Constructs a point with given coordinates.
     * @param x X coordinate.
     * @param y Y coordinate.
     */
    Point(double x, double y);

    double getX() const;
    double getY() const;

    void setX(double newX);
    void setY(double newY);

    void printInfo() const;

    /// @brief Generates a point with random coordinates.
    static Point GEN();

    /// @brief Shifts the point by dx along X axis and dy along Y axis.
    /// @param dx Shift along X.
    /// @param dy Shift along Y.
    void shift(double dx, double dy);

    /**
     * @brief Checks if point c lies on the same line as segment ab.
     * 
     * Uses cross product to verify collinearity.
     * 
     * @param a First point of the line.
     * @param b Second point of the line.
     * @param c Point to check.
     * @return true if c lies on the line through a and b, false otherwise.
     */
    static bool isOnLine(const Point& a, const Point& b, const Point& c);
};