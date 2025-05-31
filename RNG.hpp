#include <cmath>
#include <random>

using namespace std;

random_device rd;  
mt19937 gen(rd()); 
uniform_real_distribution<> dis(0.0, 1.0);