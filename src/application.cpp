#include <SFML/Graphics.hpp>
#include <iostream>
#include "drawing.hpp"
#include "random.hpp"
#include "title_screen.hpp"
#include "application.hpp"

using namespace std;

Application::Application() : w(640), h(480), font(NULL), window(NULL) { }

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
    this->w = w;
    this->h = h;
    
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
    Title_Screen title_screen(w, h, *this);

    bool quitting = false;
    // Start the game loop
    while (!quitting) {
        // *** Events ***
        sf::Event event;
        while (window->pollEvent(event)) {
            switch (event.type) {
            case sf::Event::Closed:
                quitting = true;
                break;

            case sf::Event::Resized:
                break;

            case sf::Event::KeyPressed:
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    quitting = true;
                    break;
                    
                case sf::Keyboard::F1:
                    window->capture().saveToFile("screenshot.jpg");
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

        // *** Updates ***
        // Nope
        
        // *** Draw ***
        title_screen.display(*window);
        window->display();
        
        sf::sleep(sf::seconds(0.1f));
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

sf::Font &Application::get_font() {
    return *font;
}
