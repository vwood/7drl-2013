#include <SFML/Graphics.hpp>
#include "application.hpp"
#include "drawing.hpp"
#include "random.hpp"
#include "title_screen.hpp"


Title_Screen::Title_Screen(int w, int h, Application &app) : w(w), h(h), app(app) {
    Random r;
    sf::Color background(200, 210, 255, 0);
    sf::Color text_color(80, 80, 220, 255);
    sf::Color text2_color(120, 120, 120, 255);
    
	sf::Text *text = new sf::Text("Seven Days of Midnight", app.get_font(), 32);
    text.setPosition(10, 10);
    text.setColor(text_color);
    texts.push_back(text);

	text = new sf::Text("Escape to quit, Space to play", app.get_font(), 28);
    text.setPosition(210, 440);
    text.setColor(text2_color);
    texts.push_back(text);

    sf::RectangleShape rs(sf::Vector2f(w, h / 3));
    rs.setFillColor(sf::Color(120, 120, 250, 255));
    // TODO: Create an object that can hold anything that can be drawn
    // TODO: Change to use map_objects + draw

    Drawing *m1 = Drawing::new_mountain(r, 100);
    Drawing *m2 = Drawing::new_mountain(r, 100);
    Drawing *m3 = Drawing::new_mountain(r, 100);

    Drawing *t1 = Drawing::new_tree(r, 80);
    Drawing *t2 = Drawing::new_tree(r, 80);
    Drawing *t3 = Drawing::new_tree(r, 50);

    Drawing *s1 = Drawing::new_shield(r, 100);

	sf::Text at_symbol("@", app.get_font(), 64);
    at_symbol.setPosition(550 - 32, 64 - 42);
    at_symbol.setColor(sf::Color(90, 0, 60, 255));
}
Title_Screen::~Title_Screen() {}

void Title_Screen::display(sf::RenderWindow &rw) {
    

}
