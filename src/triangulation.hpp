#ifndef TRIANGULATION_HPP
#define TRIANGULATION_HPP

#include <SFML/Graphics.hpp>
#include <vector>
class DVector;

/*
 * Triangulate a concave polygon, into separate convex polygons
 */
extern std::vector<sf::VertexArray *> *triangulate(DVector &x, DVector &y);

#endif
