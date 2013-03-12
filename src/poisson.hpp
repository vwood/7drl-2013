#ifndef POISSON_HPP
#define POISSON_HPP

#include <vector>

class Random;

class Poisson {
private:
    std::vector<double> xs;
    std::vector<double> ys;
	
	double min_dist2_to(double x, double y);

public:
    Poisson();
    ~Poisson();
	
	void generate(Random &r, int w, int h, double radius, int k, int n);
	
    const std::vector<double> &get();
};

#endif
