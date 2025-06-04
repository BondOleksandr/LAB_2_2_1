#pragma once

/**
 * @class ArrayRealization
 * @brief Abstract base class for array-like data structures.
 */
class ArrayRealization {
public:
    /**
     * @brief Prints the contents of the array.
     * 
     * Must be implemented by derived classes.
     */
    virtual void print() = 0;

    /// @brief Virtual destructor for safe polymorphic cleanup.
    virtual ~ArrayRealization();
};
