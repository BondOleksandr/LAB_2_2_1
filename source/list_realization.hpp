#pragma once

/**
 * @class ListRealization
 * @brief Abstract base class for list-like data structures.
 */
class ListRealization {
public:
    /**
     * @brief Prints the contents of the list.
     * 
     * Must be implemented by derived classes.
     */
    virtual void print() = 0;

    /// @brief Virtual destructor for safe polymorphic cleanup.
    virtual ~ListRealization();
};
