#include <SFML/Graphics.hpp>
#include <vector>
#include "drawing.hpp"

using namespace std;

Drawable::Drawable() {

}

Drawable::~Drawable() {
    for (vector<sf::VertexArray *>::iterator it=v.begin(); it != v.end(); it++) {
        delete *it;
    }
}

void Drawable::draw(sf::RenderWindow &r, double x, double y) {
    sf::Transform t;
    t.translate(x, y);
    sf::RenderStates rs(t);
    
    for (vector<sf::VertexArray *>::iterator it = v.begin(); it != v.end(); it++) {
        r.draw(**it, rs);
    }
}
