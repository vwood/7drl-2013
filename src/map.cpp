#include <SFML/Graphics.hpp>
#include "random.hpp"
#include "map.hpp"

Map::Map(int w, int h) : w(w), h(h) {
    tile_count = 5;
    tiles = new enum tile_type *[w];
    for (int i = 0; i < w; i++) {
        tiles[i] = new enum tile_type[h];
    }
}

Map::~Map() {
    for (int i = 0; i < w; i++) {
        delete[] tiles[i];
    }    
    delete[] tiles;
}

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

void Map::fill_randomly(Random &r) {
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            tiles[i][j] = (enum tile_type) r.get_int(0, tile_count-1);
        }
    }
}

void Map::draw(sf::RenderWindow &r, double x, double y, double w, double h) {
    /* TODO : display this with an offset, and fixed tile size */

    sf::RectangleShape rs(sf::Vector2f(w/this->w, h/this->h));
    
    for (int i = 0; i < this->w; i++) {
        for (int j = 0; j < this->h; j++) {
            rs.setPosition(x + i * w / this->w,
                           y + j * h / this->h);
            rs.setFillColor(get_tile_color(tiles[i][j]));
            r.draw(rs);
        }
    }
}
