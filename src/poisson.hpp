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
    Poisson() {};
	
	void generate(Random &r, int w, int h, double radius, int n, int k=10);
	
    const std::vector<double> &get_x();
    const std::vector<double> &get_y();
};

#endif
