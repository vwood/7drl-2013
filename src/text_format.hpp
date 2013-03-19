#ifndef TEXT_FORMAT_HPP
#define TEXT_FORMAT_HPP

/*
 * Formatted string printing.
 *
 * Provides wrap-around at spaces if possible, and uses
 *
 *
 */


#include <SFML/Graphics.hpp>

class Text_Format {
private:

public:
    Text_Format();
    ~Text_Format();
    void draw_format_text(sf::RenderWindow &r, const char *s, double x, double y);
};

#endif
