#include <SFML/Graphics.hpp>
#include "map.hpp"
#include "game_screen.hpp"


Game_Screen::Game_Screen(int w, int h, Map &map) : w(w), h(h), map(map) {}
Game_Screen::~Game_Screen() {}

void Game_Screen::display(sf::RenderWindow &rw) {
    map.draw(rw, 0, 0, w, h);
}
