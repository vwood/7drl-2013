#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
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
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");
 
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("img.png"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile("BenguiatBoldBT.ttf"))
        return EXIT_FAILURE;
    sf::Text text("Lords of Midnight", font, 32);

    // Load a music to play
//    sf::Music music;
//    if (!music.openFromFile("nice_music.ogg"))
//        return EXIT_FAILURE;

    // Play the music
//    music.play();

    int i;
    std::vector<sf::VertexArray> v;
    
    for (i = 0; i < 4; i++) {
        sf::VertexArray lines(sf::LinesStrip, 2);
        lines[0].position = sf::Vector2f(200 + i * 10, 100);
        lines[1].position = sf::Vector2f(200 + i * 10, 180);
        v.push_back(lines);
    }
    
    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                // window closed
            case sf::Event::Closed:
                window.close();
                break;

                // window resized
            case sf::Event::Resized:
                std::cout << "Resized: " << event.size.width << "x";
                std::cout << event.size.height << std::endl;
                break;

                // key pressed
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    window.close();
                    break;

                default:
                    std::cout << "code:" << event.key.code << std::endl;
                    break;
                }
                break;
                // we don't process other types of events
            default:
                break;
            }
        }

        // *** Draw ***
        sf::Color background(180, 180, 180, 0);
        
        // Clear screen
        window.clear(background);

        // Draw the sprite
        sprite.setPosition(0, 0);
        window.draw(sprite);
        sprite.setPosition(100, 0);
        window.draw(sprite);
        sprite.setPosition(0, 100);
        window.draw(sprite);
        
        for(std::vector<sf::VertexArray>::iterator it = v.begin(); it != v.end(); ++it) {
            window.draw(*it);
        }

        // Draw the string
        text.setPosition(10, 10);
        window.draw(text);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
