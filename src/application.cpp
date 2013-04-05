#include <SFML/Graphics.hpp>
#include <iostream>
#include "drawing.hpp"
#include "random.hpp"
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
    sf::Color background(200, 210, 255, 0);
    sf::Color text_color(80, 80, 220, 255);

	sf::Text text("Seven Days of Midnight", *font, 32);
    text.setPosition(10, 10);
    text.setColor(text_color);

	sf::Text text2("Escape to quit, Space to play", *font, 28);
    text2.setPosition(210, 440);
    text2.setColor(sf::Color(120, 120, 120, 255));

    
    sf::RectangleShape rs(sf::Vector2f(w, h / 3));
    rs.setFillColor(sf::Color(120, 120, 250, 255));

    Random r;

    // TODO: Change to use map_objects + draw

    Drawing *m1 = Drawing::new_mountain(r, 100);
    Drawing *m2 = Drawing::new_mountain(r, 100);
    Drawing *m3 = Drawing::new_mountain(r, 100);

    Drawing *t1 = Drawing::new_tree(r, 80);
    Drawing *t2 = Drawing::new_tree(r, 80);
    Drawing *t3 = Drawing::new_tree(r, 50);

    Drawing *s1 = Drawing::new_shield(r, 100);

	sf::Text at_symbol("@", *font, 64);
    at_symbol.setPosition(550 - 32, 64 - 42);
    at_symbol.setColor(sf::Color(90, 0, 60, 255));
    
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
        window->clear(background);
        window->draw(rs);
        window->draw(text);
        window->draw(text2);
        t3->draw(*window, 300.0, 170.0);
        m1->draw(*window, 120.0, 180.0);
        m2->draw(*window, 220.0, 180.0);
        m3->draw(*window, 170.0, 220.0);
        t1->draw(*window, 50.0, 240.0);
        t2->draw(*window, 90.0, 260.0);

        s1->draw(*window, 550.0, 64.0);
        window->draw(at_symbol);

        window->display();
        sf::sleep(sf::seconds(0.1f));
    }

    delete m1;
    delete m2;
    delete m3;
    
    delete t1;
    delete t2;
    delete t3;
    
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
