#include <vector>
#include "random.hpp"
#include "poisson.hpp"

using namespace std;

double Poisson::min_dist2_to(double x, double y) {
	vector<double>::iterator xit, yit;
	double min_dist = 0.0;
	bool first = true;
	
	for (xit = xs.begin(), yit = ys.begin(); xit != xs.end() && yit != ys.end(); xit++, yit++) {
		double px = *xit, py = *yit;
		double dist2 = ((px - x) * (px - x)) + ((py - y) * (py - y));
		if (first) {
			first = false;
			min_dist = dist2;
		} else if (dist2 < min_dist) {
			min_dist = dist2;
		}
	}
	return min_dist;
}

/*
 * Actually the choose best alternative sample algorithm
 * (it's easier to implement)
 *
 * TODO: generate n from the size of the polygon, so we select a density of points
 *
 * w, h = size of the area
 * radius = minimum distance between points
 * k = number of alternatives to test
 * n = total number of points to generate
 */
void Poisson::generate(Random &r, int w, int h, double radius, int k, int n) {
	xs.push_back(r.get_double(0, w));
	ys.push_back(r.get_double(0, h));

	for (int i = 0; i < n; i++) {
		double best_x = r.get_double(0, w);
		double best_y = r.get_double(0, h);
		double best_dist = min_dist2_to(best_x, best_y);

		for (int j = 1; j < k; j++) {
			double ax = r.get_double(0, w);
			double ay = r.get_double(0, h);
			double alt_dist = min_dist2_to(ax, ay);

			// Use greater than here to choose point furtherest from all others
			if (alt_dist > best_dist) { 
				best_x = ax;
				best_y = ay;
				best_dist = alt_dist;
			}
		}

		// Only add point if it is actually greater than radius
		if (best_dist > radius) { 
			xs.push_back(best_x);
			ys.push_back(best_y);
		}
	}
}
