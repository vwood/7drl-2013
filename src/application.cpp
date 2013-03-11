#include <SFML/Graphics.hpp>
#include <iostream>
#include "application.hpp"

Application::Application() { }

Application::~Application() {
    if (window) {
        window->close();
        delete window;
    }
}


void Application::init_window(int w, int h) {
    if (window) {
        window->close();
        delete window;
    }
    window = new sf::RenderWindow(sf::VideoMode(w, h), "7drl");
}

void Application::menu() {
    // Start the game loop
    while (window->isOpen()) {
        // Process events
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
                // window closed
            case sf::Event::Closed:
                window->close();
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
                    window->close();
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
        window->clear(background);

        // Update the window
        window->display();
    }
}
