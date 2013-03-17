#include "drawing.hpp"
#include "entity.hpp"

Entity::Entity(int x, int y) : x(x), y(y) {

}


Entity::~Entity() {
    if (drawing != NULL) {
        delete drawing;
    }
}
