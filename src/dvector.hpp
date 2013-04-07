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
    
    void clear();
    void set(int index, double value);
    void append(double value);
    int size();
    
    int spline_size(int k);
    void set_to_spline(DVector *other);
    
    void add(DVector *other);
    void add(double offset);

    void multiply(DVector *other);
    void multiply(double factor);
    
    void add_linear(double start, double end);
	void add_sin(double scale, double start, double end);
    void add_cos(double scale, double start, double end);
    void add_noise(Random &r, double min, double max);

	void map_sin();
	void map_cos();
	void map_abs();
	void map_neg();
	void map_midpoint_displacement(Random &r, double min, double max);
	void map_wrapped_midpoint_displacement(Random &r, double min, double max);

    const std::vector<double> &get();
};

#endif
