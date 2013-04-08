#include <SFML/Graphics.hpp>
#include <vector>
#include "dvector.hpp"
#include "triangulation.hpp"

/*
 * Returns:
 *
 * +1 if a,b,c is a ccw angle
 * -1 if a,b,c is a cw angle
 *  0 if a,b,c is co-linear
 */
int ccw(double ax, double ay, double bx, double by, double cx, double cy) {
    return (bx - ax) * (cy - ay) - (cx - ax) * (by - ay);
}

/*
 * Return true iff a intersects b
 */
bool intersects(double ax1, double ay1,
                double ax2, double ay2,
                double bx1, double by1,
                double bx2, double by2) {
    if (ccw(ax1, ay1, ax2, ay2, bx1, by1) * ccw(ax1, ay1, ax2, ay2, bx2, by2) > 0) return false;
    if (ccw(bx1, by1, bx2, by2, ax1, ay1) * ccw(bx1, by1, bx2, by2, ax2, ay2) > 0) return false;
    return true;
}

/*
 * Return true iff a->b intersects c->d, also set x&y to the point of intersection (iff true)
 */
bool intersection_point(double ax, double ay,
                        double bx, double by,
                        double cx, double cy,
                        double dx, double dy,
                        double &x, double &y) {
    double r = (ay - cy) * (dx - cx) - (ax - cx) * (dy - cy);
    double div = (bx - ax) * (dy - cy) - (by - ay) * (dx - cx);
    r = r / div;

    double s = (ay - cy) * (bx - ax) - (ax - cx) * (by - ay);
    s = s / div;

    if (0 <= r && r <= 1 && 0 <= s && s <= 1) {
        x = ax + r * (bx - ax);
        y = ay + r * (by - ay);
        return true;
    }
    
    return false;
}

vector<sf::VertexArray *> triangulation(DVector &x, DVector &y) {
    

}
