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

/*
 * Sets the vector to zeroes
 */
void DVector::clear() {
    for (vector<double>::iterator it = v.begin(); it != v.end(); it++) {
        *it = 0.0;
    }
}

/*
 * Sets a specific index to the given value
 */
void DVector::set(int index, double value) {
    v[index] = value;
}

/*
 * Add the values from another vector to this one.
 * Only adds up to the shorted vector.
 */
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
 * Add a linear sequence to the vector.
 */
void DVector::add_linear(double start, double end) {
    int size = v.size();
    int i;
    vector<double>::iterator it;
    for (it = v.begin(), i = 0; it != v.end(); it++, i++) {
        *it = *it + start + (i * (end - start) / (size-1));
    }
}

/*
 * Add a section of sine to the vector.
 *
 * start and end values are such that 1.0 is a half circle.
 */
void DVector::add_sin(double scale, double start, double end) {
    int size = v.size();
    int i;
    start *= M_PI;
    end *= M_PI;
    vector<double>::iterator it;
    for (it = v.begin(), i = 0; it != v.end(); it++, i++) {
        *it = *it + scale * sin(start + (i * (end - start) / (size-1)));
    }
}

/*
 * Add a section of cosine to the vector.
 *
 * start and end values are such that 1.0 is a half circle.
 */
void DVector::add_cos(double scale, double start, double end) {
    int size = v.size();
    int i;
    start *= M_PI;
    end *= M_PI;
    vector<double>::iterator it;
    for (it = v.begin(), i = 0; it != v.end(); it++, i++) {
        *it = *it + scale * cos(start + (i * (end - start) / (size-1)));
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

/*
 * maps sin() onto the vector.
 */
void DVector::map_sin() {
    int i;
    vector<double>::iterator it;
    for (it = v.begin(), i = 0; it != v.end(); it++, i++) {
        *it = sin(*it);
    }
}

/*
 * maps cos() onto the vector.
 */
void DVector::map_cos() {
    int i;
    vector<double>::iterator it;
    for (it = v.begin(), i = 0; it != v.end(); it++, i++) {
        *it = cos(*it);
    }
}

/*
 * maps abs() onto the vector.
 */
void DVector::map_abs() {
    int i;
    vector<double>::iterator it;
    for (it = v.begin(), i = 0; it != v.end(); it++, i++) {
        *it = fabs(*it);
    }
}

/*
 * maps -x onto the vector.
 */
void DVector::map_neg() {
    int i;
    vector<double>::iterator it;
    for (it = v.begin(), i = 0; it != v.end(); it++, i++) {
        *it = -*it;
    }
}

const vector<double> &DVector::get() {
    return v;
}
