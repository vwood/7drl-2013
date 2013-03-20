#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include "random.hpp"
#include "drawing.hpp"
#include "poisson.hpp"
#include "poly.hpp"
#include "map_object.hpp"
#include "map_color.hpp"
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
        return Map_Color::plains;
    case FOREST_TILE:
        return Map_Color::forest;
    case HILLS_TILE:
        return Map_Color::hills; 
    case WATER_TILE:
        return Map_Color::water;        
    case MOUNTAIN_TILE:
        return Map_Color::mountain;        
    default:
        return Map_Color::error;
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
        if (r.get_int(0, 10) == 0) {
            return Drawing::new_lake(r, size); // TODO: Actually a different, rare, tile type
        } else {
            return NULL;
        }
    case FOREST_TILE:
        return Drawing::new_tree(r, size);
    case HILLS_TILE:
        return Drawing::new_hill(r, size);        
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
    double radius = (max(tile_w, tile_h) / 12.0);
    radius = sqrt(2 * (radius * radius));
    p.generate(r, map_w, map_h, radius, tilemap_w * tilemap_h * 2);
    
    const std::vector<double> &xs = p.get_x();
    const std::vector<double> &ys = p.get_y();
    for (std::vector<double>::const_iterator xit = xs.begin(), yit = ys.begin();
         xit != xs.end() && yit != ys.end(); xit++, yit++) { 
        int x = (*xit / tile_w);
        int y = (*yit / tile_h);
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

bool map_object_cmp_by_y(Map_Object *a,  Map_Object *b) {
    return a->get_y() < b->get_y();
}

void Map::sort_objects() {
    sort(map_objects.begin(), map_objects.end(), map_object_cmp_by_y);
}

/*
 * Generate a map from random polygons - tiles get associated with the nearest polygon to them.
 *
 * Square polygon surrounds the world with water (or anything impassable really)
 */
void Map::poly_tile_generation(Random &r) {
    vector<Poly *> polys;
    vector<enum tile_type> poly_type;

    // outer water
    Poly *p = new Poly();
    p->add(0, 0).add(tilemap_w, 0).add(tilemap_w, tilemap_h).add(0, tilemap_h);
    polys.push_back(p);
    poly_type.push_back(WATER_TILE);

    p = new Poly();
    p->add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1))
        .add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1))
        .add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1))
        .add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1))
        .add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1));
    polys.push_back(p);
    poly_type.push_back(PLAIN_TILE);    

    p = new Poly();
    p->add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1))
        .add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1))
        .add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1))
        .add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1));
    polys.push_back(p);
    poly_type.push_back(FOREST_TILE);

    p = new Poly();
    p->add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1))
        .add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1));
    polys.push_back(p);
    poly_type.push_back(MOUNTAIN_TILE);

    p = new Poly();
    p->add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1))
        .add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1));
    polys.push_back(p);
    poly_type.push_back(MOUNTAIN_TILE);

    p = new Poly();
    p->add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1))
        .add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1))
        .add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1))
        .add(r.get_int(1, tilemap_w-1),r.get_int(1, tilemap_h-1));
    polys.push_back(p);
    poly_type.push_back(HILLS_TILE);
    
    for (int i = 0; i < tilemap_w; i++) {
        for (int j = 0; j < tilemap_h; j++) {
            double best_distance;
            bool first = true;
            vector<Poly *>::iterator it;
            int k, best_index;
            
            for (it = polys.begin(), k = 0; it != polys.end(); it++, k++) {
                double distance = (*it)->distance_to_point(i, j);
                if (first || distance < best_distance) {
                    best_distance = distance;
                    best_index = k;
                    first = false;
                }
            }
            
            tilemap[i][j] = (enum tile_type) poly_type[best_index];
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
