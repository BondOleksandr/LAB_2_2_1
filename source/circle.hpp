#pragma once

#include "figure.hpp"
#include "point.hpp"

/**
 * @class Circle
 * @brief Represents a circle defined by its center and radius.
 */
class Circle : public Figure {
private:
    Point center; ///< Center point of the circle
    double r;     ///< Radius of the circle

public:
    /**
     * @brief Constructs a circle with given center and radius.
     * @param cent Center point.
     * @param r Radius of the circle.
     */
    Circle(const Point& cent, double r);

    Point getO() const;
    double getR() const;

    void setO(Point newCenter);
    void setR(double newR);

    void shift(double dx, double dy) override;
    void printInfo() const override;

    /**
     * @brief Calculates the area of the given circle.
     * @param CL Circle to evaluate.
     * @return Area of the circle.
     */
    static double area(const Circle& CL);

    /**
     * @brief Calculates the perimeter (circumference) of the given circle.
     * @param CL Circle to evaluate.
     * @return Circumference of the circle.
     */
    static double perimeter(const Circle& CL);

    /// @brief Generates a circle with random center and radius.
    static Circle GEN();
};
