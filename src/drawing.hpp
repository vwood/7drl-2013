#ifndef DRAWING_HPP
#define DRAWING_HPP

#include <vector>

class Random;

struct point {
    double x, y;
};

extern std::vector<double> *generate_noise(int n, Random *r, double scale);
extern std::vector<double> *generate_sin(int n, double start, double end);
extern std::vector<double> *generate_cos(int n, double start, double end);
extern std::vector<struct point> *generate_circle(double x, double y, double r, int points);

#endif
