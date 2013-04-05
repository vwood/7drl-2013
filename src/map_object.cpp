#include <SFML/Graphics.hpp>
#include "drawing.hpp"
#include "map_object.hpp"

void Map_Object::draw(sf::RenderWindow &r, double x, double y) {
    drawing->draw(r, this->x + x, this->y + y);
}

Map_Object::~Map_Object() {
    delete drawing;
}
