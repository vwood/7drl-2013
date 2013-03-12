#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Random;

class Drawable {
private:
    std::vector<sf::VertexArray *> v;

public:
    Drawable();
    ~Drawable();
    
    void draw(sf::RenderWindow &r, double x, double y);
};

extern Drawable drawable_mountain();
extern Drawable drawable_tree();
extern Drawable drawable_hill();
extern Drawable drawable_wave();
extern Drawable drawable_land();

#endif
