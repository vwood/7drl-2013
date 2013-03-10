#include <time.h>
#include <stdlib.h>
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
    double result = ((double)rand_r(&seed)/(double)RAND_MAX);
    return result * (high - low) + low;
}

int Random::get_int(int low, int high) {
    double random = (double)rand_r(&seed) / (double)RAND_MAX;
    return (int)(random * (high - low)) + low;
}
