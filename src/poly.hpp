#ifndef POLY_HPP
#define POLY_HPP

#include <vector>

class Random;

class Poly {
private:
    std::vector<double> xs;
    std::vector<double> ys;
    
public:
    Poly();
    Poly(double x, double y);
    Poly(const std::vector<double> &xs, const std::vector<double> &ys);

    Poly &add(double x, double y);
    
    double area();
    double circumference();
    bool contains(double x, double y);
    double distance_to_point(double x, double y);
};

#endif
