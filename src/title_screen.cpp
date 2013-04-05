#include <SFML/Graphics.hpp>
#include <vector>
#include "application.hpp"
#include "drawing.hpp"
#include "random.hpp"
#include "map_object.hpp"
#include "title_screen.hpp"

using namespace std;

Title_Screen::Title_Screen(int w, int h, Application &app) : w(w), h(h), app(app) {
    Random r;

    sf::Color text_color(80, 80, 220, 255);
    sf::Color text2_color(120, 120, 120, 255);
    
	sf::Text *text = new sf::Text("Seven Days of Midnight", app.get_font(), 32);
    text->setPosition(10, 10);
    text->setColor(text_color);
    texts.push_back(text);

	text = new sf::Text("Escape to quit, Space to play", app.get_font(), 28);
    text->setPosition(210, 440);
    text->setColor(text2_color);
    texts.push_back(text);

	text = new sf::Text("@", app.get_font(), 64);
    text->setPosition(550 - 32, 64 - 42);
    text->setColor(sf::Color(90, 0, 60, 255));
    texts.push_back(text);
    
    background = new sf::RectangleShape(sf::Vector2f(w, h / 3));
    background->setFillColor(sf::Color(120, 120, 250, 255));

    // TODO: Create an object that can hold anything that can be drawn
    objects.push_back(new Map_Object(Drawing::new_tree(r, 50), 300.0, 170.0));
    objects.push_back(new Map_Object(Drawing::new_mountain(r, 100), 120.0, 180.0));
    objects.push_back(new Map_Object(Drawing::new_mountain(r, 100), 220.0, 180.0));
    objects.push_back(new Map_Object(Drawing::new_mountain(r, 100), 170.0, 220.0));
    objects.push_back(new Map_Object(Drawing::new_tree(r, 80), 50.0, 240.0));
    objects.push_back(new Map_Object(Drawing::new_tree(r, 80), 90.0, 260.0));
    objects.push_back(new Map_Object(Drawing::new_shield(r, 100), 550.0, 64.0));
}

Title_Screen::~Title_Screen() {
    objects.clear();
    texts.clear();
    delete background;
}

void Title_Screen::display(sf::RenderWindow &rw) {
    sf::Color bg_color(200, 210, 255, 0);
    rw.clear(bg_color);

    rw.draw(*background);

    for (vector<Map_Object*>::iterator m_it = objects.begin(); m_it != objects.end(); m_it++) {
        (*m_it)->draw(rw, 0, 0);
    }

    for (vector<sf::Text*>::iterator t_it = texts.begin(); t_it != texts.end(); t_it++) {
        rw.draw(**t_it);
    }
}
