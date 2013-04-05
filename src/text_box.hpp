#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include <SFML/Graphics.hpp>

class Text_Box {
private:
    int w, h;
    sf::Color background;

    const char *text;
    
public:
    Text_Box(int w, int h, sf::Color background);
    ~Text_Box();

    void set_text(const char *text);
    
    void display(sf::RenderWindow &rw, int x, int y);
};

#endif
