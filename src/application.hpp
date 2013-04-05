#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>

enum game_states {
    TITLE_SCREEN,
    GAME_PLAY,
    GAME_PAUSED,
    QUIT
};

class Application {
private:
    int w, h;
    sf::Font *font;
    sf::RenderWindow *window;
    enum game_states state;
    
public:
    Application();
    ~Application();    

    bool init(int w, int h);

    enum game_states title_loop();
    enum game_states game_loop();
    enum game_states paused_loop();

    void state_loop();

    sf::Font &get_font();
};

#endif
