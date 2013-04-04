#ifndef DRAWING_HPP
#define DRAWING_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Random;
class DVector;
class Map;

class Drawing {
private:
    std::vector<sf::VertexArray *> v;

public:
    Drawing();
    ~Drawing();
    
    void draw(sf::RenderWindow &r, double x, double y);

    static Drawing *new_mountain(Random &r, double size);
    static Drawing *new_tree(Random &r, double size);
    static Drawing *new_hill(Random &r, double size);
    static Drawing *new_wave(Random &r, double size);
    static Drawing *new_lake(Random &r, double size);
    static Drawing *new_land(Random &r, double size);

    static Drawing *new_tower(Random &r, double size);
    static Drawing *new_keep(Random &r, double size);
    static Drawing *new_hut(Random &r, double size);

    static Drawing *new_shield(Random &r, double size);
    static Drawing *new_person(Random &r, double size);

    static Drawing *new_landmass(Random &r, Map &m, int tile);
};


#endif
