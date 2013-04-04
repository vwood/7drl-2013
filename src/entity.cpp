#include "random.hpp"
#include "drawing.hpp"
#include "entity.hpp"

Entity::Entity(Random &r, int x, int y) : x(x), y(y) {
    drawing = Drawing::new_person(r, 16);
}


Entity::~Entity() {
    if (drawing != NULL) {
        delete drawing;
    }
}

void Entity::draw(sf::RenderWindow &r, double x, double y, double tile_w, double tile_h) {
    drawing->draw(r, this->x * tile_w + tile_w / 2 + x, this->y * tile_h + tile_h / 2 + y);
}
