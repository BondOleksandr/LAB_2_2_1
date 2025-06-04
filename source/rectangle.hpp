#pragma once

#include <iostream>
#include <cmath>
#include "point.hpp"
#include "line.hpp"
#include "figure.hpp"

/**
 * @class Rectangle
 * @brief Represents a quadrilateral with four points, assumed to form a rectangle.
 */
class Rectangle : public Figure {
private:
    Point a, b, c, d; ///< Vertices of the rectangle in order

public:
    /**
     * @brief Constructs a rectangle from four given points.
     * @param a First vertex.
     * @param b Second vertex.
     * @param c Third vertex.
     * @param d Fourth vertex.
     */
    Rectangle(const Point& a, const Point& b, const Point& c, const Point& d);

    Point getA() const;
    Point getB() const;
    Point getC() const;
    Point getD() const;

    void setA(const Point& newA);
    void setB(const Point& newB);
    void setC(const Point& newC);
    void setD(const Point& newD);

    /// @brief Generates a random rectangle.
    static Rectangle GEN();

    void printInfo() const override;

    /// @brief Applies a shift to all four points of the rectangle.
    /// @param dx Shift along X axis.
    /// @param dy Shift along Y axis.
    void shift(double dx, double dy) override;

    /**
     * @brief Checks if the given rectangle is convex.
     * 
     * Convexity implies all internal angles are less than 180 degrees.
     * 
     * @param ABCD Rectangle to check.
     * @return true if convex, false otherwise.
     */
    static bool isconvex(const Rectangle& ABCD);

    /**
     * @brief Calculates the perimeter of the rectangle.
     * @param ABCD Rectangle to evaluate.
     * @return Perimeter of the rectangle.
     */
    static double perimeter(const Rectangle& ABCD);

    /**
     * @brief Calculates the area of the rectangle.
     * @param ABCD Rectangle to evaluate.
     * @return Area of the rectangle.
     */
    static double area(const Rectangle& ABCD);
};
