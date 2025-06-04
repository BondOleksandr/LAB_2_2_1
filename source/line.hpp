#pragma once
#include <iostream>
#include <cmath>
#include "point.hpp"

using namespace std;

/**
 * @class Line
 * @brief Represents a line segment defined by two Points in 2D space.
 */
class Line {
private:
    Point BEG; ///< Starting point of the line
    Point END; ///< Ending point of the line

public:
    /**
     * @brief Constructs a line segment from two points.
     * @param a Starting point.
     * @param b Ending point.
     */
    Line(const Point& a, const Point& b);

    Point getPointBEG() const;
    Point getPointEND() const;
    void printInfo() const;

    /// @brief Generates a line from random points.
    static Line GEN();

    /**
     * @brief Checks if two lines are parallel.
     * 
     * Compares the slopes of the lines.
     * 
     * @param z First line.
     * @param u Second line.
     * @return true if lines are parallel, false otherwise.
     */
    static bool isParalel(const Line& z, Line& u);

    /**
     * @brief Returns the point of intersection of two lines.
     * 
     * If the lines are parallel, returns a placeholder point.
     * 
     * @param z First line.
     * @param u Second line.
     * @return Intersection point.
     */
    static Point crossing(const Line& z, Line& u);

    /**
     * @brief Returns the angle between two lines in radians.
     * 
     * Uses vector dot product and arccos.
     * 
     * @param z First line.
     * @param u Second line.
     * @return Angle in radians.
     */
    static double angle(const Line& z, Line& u);

    /**
     * @brief Returns the Euclidean length of the given line.
     * @param z Line whose length to compute.
     * @return Length of the line.
     */
    static double LLength(const Line& z);
};
