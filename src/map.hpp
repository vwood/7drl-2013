#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Drawing;
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
    /* In pixels - entire map */
    int map_w, map_h;
    
    /* In pixels - single tile */
    int tile_w, tile_h;

    /* In tiles - entire map */
    int tilemap_w, tilemap_h;

    
    enum tile_type **tilemap;
    std::vector<Map_Object*> map_objects;

    static const int tile_count = 5;
    static sf::Color get_tile_color(enum tile_type tile);
    static bool tile_blocks_move(enum tile_type tile);
    static bool tile_blocks_sight(enum tile_type tile);
    Drawing *create_tile_object(Random &r, enum tile_type tile);
    
public:

    Map(int map_w, int map_h, int tile_w, int tile_h);
    ~Map();

    void fill_tiles_randomly(Random &r);
    void fill_objects_randomly(Random &r);    

    void add_object(Map_Object *object);
    void draw(sf::RenderWindow &r, double x, double y, double w, double h);
};

#endif
