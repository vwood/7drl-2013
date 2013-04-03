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
