#ifndef POLY_HPP
#define POLY_HPP

#include <vector>

class Random;

class Poly {
private:
    std::vector<double> xs;
    std::vector<double> ys;
    
public:
    Poly(Random &r, double x, double y, double radius);
    
    double area();
    double circumference();
    bool contains(double x, double y);
    double distance_to_point(double x, double y);
};

#endif
