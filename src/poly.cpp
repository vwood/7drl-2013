#include <math.h>
#include <vector>
#include "poly.hpp"

using namespace std;

double point_point_distance(double x1, double y1, double x2, double y2) {
    return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

/*
 * Returns the point point distance squared
 */
double point_point_distance2(double x1, double y1, double x2, double y2) {
    return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
}

/*
 * Returns the distance from a point to a line segment
 */
double point_line_distance(double x, double y, double x1, double y1, double x2, double y2) {
    double l2 = point_point_distance2(x1, y1, x2, y2);

    if (l2 == 0) {
        // line segment is a point
        return point_point_distance(x, y, x1, y1);
    }

    double t = ((x - x1) * (x2 - x1) + (y - y1) * (y2 - y1)) / l2;

    if (t < 0) {
        // closest to end point 1
        return point_point_distance(x, y, x1, y1);
    } else if (t > 1) {
        // closest to end point 2
        return point_point_distance(x, y, x2, y2);
    }

    return point_point_distance(x1 + t * (x2 - x1), y1 + t * (y2 - y1), x, y);
}

double Poly::area() {
    double area = 0;
    double last_x = xs[xs.size()-1], last_y = ys[ys.size()-1];
    
    for (vector<double>::iterator xit = xs.begin(), yit = ys.begin(); xit != xs.end() && yit != ys.end(); xit++, yit++) {
        area += last_x * (*yit) - (*xit) * last_y;
        last_x = *xit;
        last_y = *yit;
    }

    return fabs(area / 2);
}

double Poly::circumference() {
    double circumference = 0;
    double last_x = xs[xs.size()-1], last_y = ys[ys.size()-1];
    
    for (vector<double>::iterator xit = xs.begin(), yit = ys.begin(); xit != xs.end() && yit != ys.end(); xit++, yit++) {
        circumference += point_point_distance(*xit, *yit, last_x, last_y);
        last_x = *xit;
        last_y = *yit;
    }

    return circumference;
}

bool Poly::contains(double x, double y) {
    bool result = false;
    double last_x = xs[xs.size()-1], last_y = ys[ys.size()-1];
    
    for (vector<double>::iterator xit = xs.begin(), yit = ys.begin(); xit != xs.end() && yit != ys.end(); xit++, yit++) {
        if (((last_y > y) != ((*yit) > y)) &&
            (x < (last_x - (*xit)) * (y - (*yit)) / (last_y - (*yit)) + (*xit))) {
            result = !result;
        }

        last_x = *xit;
        last_y = *yit;
    }

    return result;
}

double Poly::distance_to_point(double x, double y) {
    double min_distance = 0;
    bool first = true;

    double last_x = xs[xs.size()-1], last_y = ys[ys.size()-1];
    
    for (vector<double>::iterator xit = xs.begin(), yit = ys.begin(); xit != xs.end() && yit != ys.end(); xit++, yit++) {
        double distance = point_line_distance(x, y, last_x, last_y, *xit, *yit);
        if (first || distance < min_distance) {
            min_distance = distance;
            first = false;
        }            

        last_x = *xit;
        last_y = *yit;
    }

    return min_distance;
}
