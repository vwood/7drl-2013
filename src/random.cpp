#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "random.hpp"

using namespace std;

Random::Random() {
    seed = time(NULL);
}

void Random::set_seed(unsigned int seed) {
    this->seed = seed;
}

unsigned int Random::get_seed() {
    return seed;
}

double Random::get_double(double low, double high) {
    srand(seed);
	double result = (double)rand() / (double)RAND_MAX;
    seed = rand() + (rand() << 16);
    return result * (high - low) + low;
}

int Random::get_int(int low, int high) {
    srand(seed);    
    double random = (double)rand() / (double)RAND_MAX;
    seed = rand() + (rand() << 16);
    return (int)(random * (high - low)) + low;
}
