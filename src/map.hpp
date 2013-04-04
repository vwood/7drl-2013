#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <SFML/Graphics.hpp>

class Drawing;
class Random;
class Map_Object;
class Entity;

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

    std::vector<Entity*> entities;

    static const int tile_count = 5;

    static bool tile_blocks_move(enum tile_type tile);
    static bool tile_blocks_sight(enum tile_type tile);
    Drawing *create_tile_object(Random &r, enum tile_type tile);
    
public:
    static sf::Color get_tile_color(enum tile_type tile);
    
    Map(int map_w, int map_h, int tile_w, int tile_h);
    ~Map();

    void fill_tiles_randomly(Random &r);
    void fill_objects_randomly(Random &r);
    void fill_entities_randomly(Random &r, int n);
    void sort_map_objects();

    void poly_tile_generation(Random &r);    

    void add_object(Map_Object *object);
    void add_entity(Entity *entity);
    void draw(sf::RenderWindow &r, double x, double y, double w, double h);

    enum tile_type get_tile_at(int x, int y);
    int get_tile_width();
    int get_tile_height();
};

#endif
