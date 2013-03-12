#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "application.hpp"
#include "dvector.hpp"

using namespace std;

void draw(const vector<double> &x, const vector<double> &y) {
    sf::VertexArray lines(sf::LinesStrip, min(x.size(), y.size()));
    vector<double>::const_iterator xit, yit;
    int i;
    for(xit = x.begin(), yit = y.begin(), i = 0;
        xit != x.end() && yit != y.end();
        xit++, yit++, i++) {
        lines[i].position = sf::Vector2f(*xit, *yit);
    }
}

int main() {
    Application game;

    if (!game.init(640, 480)) {
        cerr << "Error during initialisation." << endl;
        return 1;
    }

    game.state_loop();
    return 0;
}
