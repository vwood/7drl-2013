#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Random;
class Map_Object;

enum tile_type {
    PLAIN_TILE,
    FOREST_TILE,
    HILLS_TILE,
    WATER_TILE,
    MOUNTAIN_TILE
};

class Map {
private:
    int w, h;
    int tile_count;
    enum tile_type **tiles;
    std::vector<Map_Object*> map_objects;

    static sf::Color get_tile_color(enum tile_type tile);
    
public:
    Map(int w, int h);
    ~Map();

    void fill_randomly(Random &r);

    void add_object(Map_Object *object);
    void draw(sf::RenderWindow &r, double x, double y, double w, double h);
};

#endif
