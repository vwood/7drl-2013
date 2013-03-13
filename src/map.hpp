#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Map_Object;

class Map {
private:
    int w, h;
    int **tiles;
    std::vector<Map_Object*> map_objects;

public:
    Map(int w, int h);
    ~Map();

    void add_object(Map_Object *object);
    void draw(sf::RenderWindow r, double x, double y);
};

#endif
