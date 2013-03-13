#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

class Random;
class Drawing;

class Map {
private:
    int w, h;
    int **tiles;

public:
    Map(int w, int h);
    ~Map();
};

#endif
