#include <vector>
#include <math.h>
#include "drawing.hpp"
#include "random.hpp"

using namespace std;

vector<double> *generate_noise(int n, Random *r, double scale) {
    vector<double> *result = new vector<double>();

    for (int i = 0; i < n; i++) {
        result->push_back(r->get_double(-scale, scale));
    }

    return result;
}
