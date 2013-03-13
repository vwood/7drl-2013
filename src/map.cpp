#include "map.hpp"

Map::Map(int w, int h) : w(w), h(h) {
    tiles = new int *[w];
    for (int i = 0; i < w; i++) {
        tiles[i] = new int[h];
    }
}

Map::~Map() {
    for (int i = 0; i < w; i++) {
        delete[] tiles[i];
    }    
    delete[] tiles;
}
