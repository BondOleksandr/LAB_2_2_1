#pragma once
#include <random>

/// @brief Random device used for seeding the generator.
extern std::random_device rd;

/// @brief Mersenne Twister 19937 random number generator.
extern std::mt19937 gen;

/// @brief Uniform real distribution in a specified range (typically [0,1]).
extern std::uniform_real_distribution<> dis;

/**
 * @brief Generates a dynamically allocated square matrix filled with random values.
 * 
 * @param size The number of rows and columns in the square matrix.
 * @return Pointer to a dynamically allocated 2D array of size [size x size].
 */
double** MATGEN(int size);

/**
 * @brief Generates a dynamically allocated vector filled with random values.
 * 
 * @param size The number of elements in the vector.
 * @return Pointer to a dynamically allocated array of size [size].
 */
double* VECGEN(int size);
