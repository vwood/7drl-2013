#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <iostream>
#include "random.hpp"
#include "drawing.hpp"
#include "poisson.hpp"
#include "map_object.hpp"
#include "map.hpp"

using namespace std;

Map::Map(int map_w, int map_h, int tile_w, int tile_h) : map_w(map_w), map_h(map_h), tile_w(tile_w), tile_h(tile_h) {
    tilemap_w = map_w / tile_w;
    tilemap_h = map_h / tile_h;
    
    tilemap = new enum tile_type *[tilemap_w];
    for (int i = 0; i < tilemap_w; i++) {
        tilemap[i] = new enum tile_type[tilemap_h];
    }
}

Map::~Map() {
    for (int i = 0; i < tilemap_w; i++) {
        delete[] tilemap[i];
    }    
    delete[] tilemap;

    for (vector<Map_Object*>::iterator it = map_objects.begin(); it != map_objects.end(); it++) {
        delete *it;
    }
}

/*
 * Get the colour to display under a given tile_type
 */
sf::Color Map::get_tile_color(enum tile_type tile) {
    switch (tile) {
    case PLAIN_TILE:
        return sf::Color(240, 240, 240, 255);
    case FOREST_TILE:
        return sf::Color(50, 220, 120, 255);
    case HILLS_TILE:
        return sf::Color(240, 210, 180, 255);
    case WATER_TILE:
        return sf::Color(50, 120, 220, 255);
    case MOUNTAIN_TILE:
        return sf::Color(180, 180, 180, 255);
    default:
        return sf::Color(255, 0, 255, 255); // Angry Magenta Error
    }
}

/*
 * Predicate to test if a tile_type blocks movement
 */
bool Map::tile_blocks_move(enum tile_type tile) {
    switch (tile) {
    case PLAIN_TILE:
    case HILLS_TILE:
    case FOREST_TILE:
        return false;
    case WATER_TILE:
    case MOUNTAIN_TILE:
    default:
        return true;
    }
}

/*
 * Predicate to test if a tile_type blocks sight
 */
bool Map::tile_blocks_sight(enum tile_type tile) {
    switch (tile) {
    case PLAIN_TILE:
        return false;
    case HILLS_TILE:
    case FOREST_TILE:
    case WATER_TILE:
    case MOUNTAIN_TILE:
    default:
        return true;
    }
}

/*
 * Get the Drawing object for a given tile object.
 *
 * NULL is possible for tiles without objects
 */
Drawing *Map::create_tile_object(Random &r, enum tile_type tile) {
    double size = max(tile_w, tile_h);
    switch (tile) {
    case PLAIN_TILE:
        return NULL;
    case FOREST_TILE:
        return Drawing::new_tree(r, size);
    case HILLS_TILE:
        return NULL; /* TODO: create a hill object */
    case WATER_TILE:
        return Drawing::new_wave(r, size);
    case MOUNTAIN_TILE:
        return Drawing::new_mountain(r, size);
    default:
        return NULL;
    }
}

void Map::fill_tiles_randomly(Random &r) {
    for (int i = 0; i < tilemap_w; i++) {
        for (int j = 0; j < tilemap_h; j++) {
            tilemap[i][j] = (enum tile_type) r.get_int(0, tile_count);
        }
    }
}

void Map::fill_objects_randomly(Random &r) {
    Poisson p;
    double radius = (max(tile_w, tile_h) / 4.0);
    radius = sqrt(2 * (radius * radius));
    p.generate(r, map_w, map_h, radius, 120);

    const std::vector<double> &xs = p.get_x();
    const std::vector<double> &ys = p.get_y();
    for (std::vector<double>::const_iterator xit = xs.begin(), yit = ys.begin();
         xit != xs.end() && yit != ys.end(); xit++, yit++) { 
        int x = *xit / tile_w;
        int y = *yit / tile_h;
        if (x < 0 || x >= tilemap_w || y < 0 || y >= tilemap_h) {
            cerr << "Error: poisson generated outside tilemap. " << x << "x" << y << endl;
            continue;
        }
        Drawing *d = create_tile_object(r, tilemap[x][y]);
        if (d != NULL) {
            map_objects.push_back(new Map_Object(d, *xit, *yit));
        }
    }
}

/*
 * Adds a map object to the map
 *
 * Here we map the object to tiles. 
 */
void Map::add_object(Map_Object *object) {
    map_objects.push_back(object);
}

void Map::draw(sf::RenderWindow &r, double x, double y, double w, double h) {
    /* TODO : display this with an offset, and fixed tile size */
    /* TODO : use a camera object */
    sf::RectangleShape rs(sf::Vector2f(w/tilemap_w, h/tilemap_h));
    
    for (int i = 0; i < tilemap_w; i++) {
        for (int j = 0; j < tilemap_h; j++) {
            rs.setPosition(x + i * w / tilemap_w,
                           y + j * h / tilemap_h);
            rs.setFillColor(get_tile_color(tilemap[i][j]));
            r.draw(rs);
        }
    }

    for (vector<Map_Object*>::iterator it = map_objects.begin(); it != map_objects.end(); it++) {
        (*it)->draw(r, 0, 0);
    }
}
