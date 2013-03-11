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
	
    void add_linear(double start, double end);
	void add_sin(double scale, double start, double end);
    void add_cos(double scale, double start, double end);
    void add_noise(Random &r, double scale);

	void map_sin();
	void map_cos();
	void map_abs();
	void map_neg();	

    const std::vector<double> &get();
};

#endif
