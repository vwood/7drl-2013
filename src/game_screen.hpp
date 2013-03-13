#ifndef GAME_SCREEN_HPP
#define GAME_SCREEN_HPP

#include <SFML/Graphics.hpp>

class Game_Screen {
private:
    
public:
    Game_Screen();
    ~Game_Screen();

    void display(sf::RenderWindow &rw);
};

#endif
