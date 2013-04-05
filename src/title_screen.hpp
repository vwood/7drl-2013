#ifndef TITLE_SCREEN_HPP
#define TITLE_SCREEN_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Application;
class Map_Object;

class Title_Screen {
private:
    int w, h;
    Application &app;
    std::vector<Map_Object *> objects;
    std::vector<sf::Text *> texts;
    sf::RectangleShape *background;
    
public:
    Title_Screen(int w, int h, Application &app);
    ~Title_Screen();

    void display(sf::RenderWindow &rw);
};

#endif
