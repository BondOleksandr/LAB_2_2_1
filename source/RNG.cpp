#include "RNG.hpp"
#include <cstdlib>  // rand()
using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(0.0, 1.0);

double** MATGEN(int size) {
    double** MAT = new double*[size];
    for (int i = 0; i < size; i++) {
        MAT[i] = new double[size];
    }
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if ((rand() % 100) > 80) {
                MAT[i][j] = dis(gen) * (rand() % 100);
            } else {
                MAT[i][j] = 0;
            }
        }
    }
    return MAT;
}

double* VECGEN(int size) {
    double* VEC = new double[size];
    for (int i = 0; i < size; i++) {
        if ((rand() % 100) > 80) {
            VEC[i] = dis(gen) * (rand() % 100);
        } else {
            VEC[i] = 0;
        }
    }
    return VEC;
}
