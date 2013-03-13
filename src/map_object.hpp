#ifndef MAP_OBJECT_HPP
#define MAP_OBJECT_HPP

/*
 * Objects placed on the map (nothing to do with the tiles.)
 */

#include <SFML/Graphics.hpp>
class Drawing;

class Map_Object {
private:
    Drawing *drawing;
    double x, y;

public:
    Map_Object(Drawing *drawing, double x, double y) : drawing(drawing), x(x), y(y) {}

    void draw(sf::RenderWindow r, double x, double y);
};
