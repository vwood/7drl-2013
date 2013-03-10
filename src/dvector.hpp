#ifndef DVECTOR_HPP
#define DVECTOR_HPP

#include <vector>

class Random;

class DVector {
private:
    std::vector<double> v;

public:
    DVector(int n);
    DVector(const DVector &copy);
    
    void set_zero();
    void add(DVector *other);
    void add(double offset);
    void scale(double factor);
    void add_sin(double start, double end);
    void add_cos(double start, double end);
    void add_noise(Random &r, double scale);
};

#endif
