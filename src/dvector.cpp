#include <vector>
#include <math.h>
#include "random.hpp"
#include "dvector.hpp"

using namespace std;

DVector::DVector(int n) {
    int i;

    for (i = 0; i < n; i++) {
        this->v.push_back(0.0);
    }
}

DVector::DVector(const DVector &copy) {
    for (vector<double>::const_reverse_iterator rit = copy.v.rbegin(); rit != copy.v.rend(); rit++) {
        this->v.push_back(*rit);
    }
}

void DVector::set_zero() {
    for (vector<double>::iterator it = v.begin(); it != v.end(); it++) {
        *it = 0.0;
    }
}

void DVector::add(DVector *other) {
    for (vector<double>::iterator it = v.begin(), oit = other->v.begin(); oit != other->v.end() && it != v.end(); oit++, it++) {
        *it = *it + *oit;
    }
}

/*
 * Translate a vector by an offset
 */
void DVector::add(double offset) {
    for (vector<double>::iterator it = v.begin(); it != v.end(); it++) {
        *it = *it + offset;
    }
}

/*
 * Scale the vector by the given value
 */
void DVector::scale(double factor) {
    for (vector<double>::iterator it = v.begin(); it != v.end(); it++) {
        *it = *it * factor;
    }
}

/*
 * Add a section of sine to the vector.
 *
 * start and end values are such that 1.0 is a full circle.
 */
void DVector::add_sin(double start, double end) {
    int size = v.size();
    int i;
    start *= M_PI;
    end *= M_PI;
    vector<double>::iterator it;
    for (it = v.begin(), i = 0;
         it != v.end(); it++, i++) {
        *it = sin(start + (i * (end - start) / (size-1)));
    }
}

/*
 * Add a section of cosine to the vector.
 *
 * start and end values are such that 1.0 is a full circle.
 */
void DVector::add_cos(double start, double end) {
    int size = v.size();
    int i;
    start *= M_PI;
    end *= M_PI;
    vector<double>::iterator it;
    for (it = v.begin(), i = 0; it != v.end(); it++, i++) {
        *it = cos(start + (i * (end - start) / (size-1)));
    }
}

/*
 * Add noise to the vector.
 */
void DVector::add_noise(Random &r, double scale) {
    for (vector<double>::iterator it = v.begin(); it != v.end(); it++) {
        *it = *it + r.get_double(-scale, scale);
    }
}
