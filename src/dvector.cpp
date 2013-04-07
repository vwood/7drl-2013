#include <vector>
#include <math.h>
#include <iostream>
#include "random.hpp"
#include "dvector.hpp"

using namespace std;

DVector::DVector(int n) {
    for (int i = 0; i < n; i++) {
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
 * Adds a given value to the end of the DVector, increasing its size
 */
void DVector::append(double value) {
    v.push_back(value);
}

int DVector::size() {
    return v.size();
}

/*
 * Helper function for Catmull-Rom splines (goes through all points) 
 * t is the fraction between 0 and 1 that the point is between p1 & p2
 */ 
double catmull_rom(double t, double p0, double p1, double p2, double p3) {
    return p1 + 0.5 * ((p2 - p0) * t + (2*p0 - 5*p1 + 4*p2 - p3) * (t*t) + (3*p1 - p0 - 3*p2 + p3) * (t*t*t));
}

/*
 * Returns the size to use for a DVector to have a spline from this DVector with a given k (segment size)
 */
int DVector::spline_size(int k) {
    return k * (v.size() - 3) + 1;
}

/*
 * Sets the DVector to be a spline defined by the points in the other DVector
 *
 * For now, the first point and last point are not reached by the spline
 *
 * This DVector should have a number of points equal to:
 *  
 *   k(n-1)+1
 *
 * Where n is the number in the other DVector, and k is some multiple
 */
void DVector::set_to_spline(DVector *other) {
    int size = this->v.size();
    int osize = other->v.size();
    int section_count = osize - 3;
    int section_size = (size - 1) / section_count;

//    cout << size << " " << osize << " " << section_count << " " << section_size << endl;
    
    for (int i = 0; i < size - 1; i++) {
        int section = i / section_size + 1; // skip initial section
        double t, x0, x1, x2, x3;
        t = (i % section_size) / (double)section_size;

//        cout << "i:" << i << " section:" << section << " t:" << t << endl;
        x0 = other->v[section-1];
        x1 = other->v[section];
        x2 = other->v[section+1];
        x3 = other->v[section+2];
        this->v[i] = catmull_rom(t, x0, x1, x2, x3);
    }

    // Last vertex is a special case
    this->v[size-1] = other->v[osize-2]; 
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
 * Multiply the vector by the values in the other vector
 */
void DVector::multiply(DVector *other) {
    for (vector<double>::iterator it = v.begin(), oit = other->v.begin(); oit != other->v.end() && it != v.end(); oit++, it++) {
        *it = *it * *oit;
    }
}

/*
 * Multiply the vector by the given value
 */
void DVector::multiply(double factor) {
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
void DVector::add_noise(Random &r, double min, double max) {
    for (vector<double>::iterator it = v.begin(); it != v.end(); it++) {
        *it = *it + r.get_double(min, max);
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

/*
 * Performs wrapped midpoint displacement to the vector.
 *
 * add_noise() first (starting points are 0, and size/2)
 */
void DVector::map_wrapped_midpoint_displacement(Random &r, double min, double max) {
	int size = v.size();
	double displacement[size + 1];
	displacement[0] = v[0];
	displacement[size/2] = v[size/2];
	displacement[size] = v[0];
	midpoint_displacement(r, displacement, 0, size/2, min, max);
	midpoint_displacement(r, displacement, size/2, size, min, max);
	int i;
	vector<double>::iterator it;
    for (i = 0, it = v.begin(); it != v.end(); i++, it++) {
        *it = displacement[i];
    }
}

const vector<double> &DVector::get() {
    return v;
}
