#pragma once

#include <iostream>
#include <cmath>
#include "point.hpp"
#include "line.hpp"
#include "figure.hpp"

/**
 * @class Triangle
 * @brief Represents a triangle defined by three 2D points.
 */
class Triangle : public Figure {
private:
    Point a, b, c; ///< Vertices of the triangle

public:
    /**
     * @brief Constructs a triangle from three given points.
     * @param a First vertex.
     * @param b Second vertex.
     * @param c Third vertex.
     */
    Triangle(const Point& a, const Point& b, const Point& c);

    Point getA() const;
    Point getB() const;
    Point getC() const;

    void setA(const Point& newA);
    void setB(const Point& newB);
    void setC(const Point& newC);

    /// @brief Generates a triangle with random vertices.
    static Triangle GEN();

    void printInfo() const override;

    /// @brief Applies shift to all triangle vertices.
    /// @param dx Shift along X axis.
    /// @param dy Shift along Y axis.
    void shift(double dx, double dy) override;

    /**
     * @brief Calculates the area of a triangle using two sides and sine of the angle between them.
     * @param ABC Triangle whose area to compute.
     * @return Area of the triangle.
     */
    static double area(const Triangle& ABC);

    /**
     * @brief Returns the circumcenter of the triangle.
     * 
     * The point where the perpendicular bisectors of the sides intersect.
     * 
     * @param ABC Triangle to evaluate.
     * @return Circumcenter point.
     */
    static Point outcircle(const Triangle& ABC);

    /**
     * @brief Returns the incenter of the triangle.
     * 
     * The point where the angle bisectors intersect.
     * 
     * @param ABC Triangle to evaluate.
     * @return Incenter point.
     */
    static Point incircle(const Triangle& ABC);

    /**
     * @brief Calculates the perimeter of the triangle.
     * @param ABC Triangle to evaluate.
     * @return Perimeter value.
     */
    static double perimeter(const Triangle& ABC);

    /**
     * @brief Checks whether two triangles are similar.
     * 
     * Compares corresponding angles or ratios of sides.
     * 
     * @param ABC First triangle.
     * @param XYZ Second triangle.
     * @return true if triangles are similar, false otherwise.
     */
    static bool issimilar(const Triangle& ABC, const Triangle& XYZ);
};
