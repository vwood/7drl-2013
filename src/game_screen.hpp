#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include <SFML/Graphics.hpp>

class Map;

class Game_Screen {
private:
    int w, h;
    Map &map;
    
public:
    Game_Screen(int w, int h, Map &map);
    ~Game_Screen();

    void display(sf::RenderWindow &rw);
};

#endif
