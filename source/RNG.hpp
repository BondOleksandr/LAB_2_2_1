#pragma once
#include <random>

extern std::random_device rd;
extern std::mt19937 gen;
extern std::uniform_real_distribution<> dis;

double** MATGEN(int size);
double* VECGEN(int size);