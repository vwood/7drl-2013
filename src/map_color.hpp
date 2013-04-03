#ifndef MAP_COLOR_HPP
#define MAP_COLOR_HPP

#include <SFML/Graphics.hpp>

class Map_Color {
public:
    static const sf::Color plains;
    static const sf::Color forest;
    static const sf::Color hills;
    static const sf::Color water;
    static const sf::Color mountain;
    static const sf::Color error;

    static const sf::Color outlines;
    static const sf::Color mountain_back;
    static const sf::Color mountain_front;
    static const sf::Color tree_leaves;
    static const sf::Color tree_trunk;
    static const sf::Color hill_back;
    static const sf::Color hill_front;
    static const sf::Color wave;
    static const sf::Color lake;

    static const sf::Color shield;

    static const sf::Color person_head;
    static const sf::Color person_body;
};

#endif
