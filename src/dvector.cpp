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


/*
 * Provides displacement in the array, assuming a[s] and a[e] are the ends of the array, which are set
 *
 * min & max are the min and max of the displacement.
 */
void midpoint_displacement(Random &r, double a[], int s, int e, double min, double max) {
	if (e - s <= 1) return;
	int mid = s + (e-s)/2;
	
	if (mid != s && mid != e) {
		a[mid] = a[s] + (a[e]-a[s]) * r.get_double(min, max);
	}

	midpoint_displacement(r, a, s, mid, min, max);
	midpoint_displacement(r, a, mid, e, min, max);
}

/*
 * Performs midpoint displacement to the vector.
 *
 * Uses current endpoints of the vector
 * min and max are the limits on the amount of displacement to perform
 */
void DVector::map_midpoint_displacement(Random &r, double min, double max) {
	int size = v.size();
	double displacement[size];
	displacement[0] = v[0];
	displacement[size-1] = v[size-1];
	midpoint_displacement(r, displacement, 0, size-1, min, max);
	int i;
	vector<double>::iterator it;
    for (i = 0, it = v.begin(); it != v.end(); i++, it++) {
        *it = displacement[i];
    }
}

const vector<double> &DVector::get() {
    return v;
}
