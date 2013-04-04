#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity {
private:
    int x, y;
    Drawing *drawing;
    
public:
    Entity(Random &r, int x, int y);
    ~Entity();

    void draw(sf::RenderWindow &r, double x, double y, double tile_w, double tile_h);
};

#endif
