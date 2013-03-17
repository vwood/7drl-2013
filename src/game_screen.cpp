#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "game_screen.hpp"


Game_Screen::Game_Screen(int x, int y) : x(x), y(y) {}
Game_Screen::~Game_Screen() {}

void Game_Screen::display(sf::RenderWindow &rw, Map &map) {
    map.draw(rw, 0, 0, 640, 480);
}


