#include <SFML/Graphics.hpp>
#include <iostream>
#include "application.hpp"

using namespace std;

Application::Application() {
	font = NULL;
	window = NULL;
}

Application::~Application() {
    if (window) {
        window->close();
        delete window;
    }

	if (font) {
		delete font;
	}
}

/*
 * Load/Create resources, returns false iff it has failed.
 */
bool Application::init(int w, int h) {
    if (window) {
        window->close();
        delete window;
    }

	font = new sf::Font();
    font->loadFromFile("resources/BenguiatBoldBT.ttf");
    if (!font) {
        return false;
    }

    window = new sf::RenderWindow(sf::VideoMode(w, h), "7drl");
    if (!window) {
        return false;
    }
    
    return true;
}

enum game_states Application::title_loop() {
    sf::Color background(200, 210, 255, 0);
    sf::Color text_color(100, 100, 220, 255);

	sf::Text text("Seven Days of Midnight", *font, 32);
    text.setPosition(10, 10);
    text.setColor(text_color);
    
    // Start the game loop
    while (window->isOpen()) {
        // Process events
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
                // window closed
            case sf::Event::Closed:
                window->close();
                return QUIT;
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
                    return QUIT;
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
        window->clear(background);
        window->draw(text);

        // Update the window
        window->display();
    }

    return QUIT;
}

enum game_states Application::game_loop() {
    return QUIT;
}

enum game_states Application::paused_loop() {
    return QUIT;
}


void Application::state_loop() {
	state = TITLE_SCREEN;

    bool quitting = false;
    while (!quitting) {
        switch (state) {
        case TITLE_SCREEN:
            state = title_loop();
            break;
        case GAME_PLAY:
            state = game_loop();
            break;
        case GAME_PAUSED:
            state = paused_loop();
            break;
        case QUIT:
            quitting = true;
            break;
        default:
            cerr << "Error: Unexpected state transition, quitting." << endl;
            quitting = true;
            break;
        }
    }
}
