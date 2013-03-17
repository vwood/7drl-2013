#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include <SFML/Graphics.hpp>

class Map;

class Game_Screen {
private:
    int x, y;
public:
    Game_Screen(int x, int y);
    ~Game_Screen();

    void display(sf::RenderWindow &rw, Map &map);
};

#endif
