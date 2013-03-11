#ifndef APPLICATION_HPP
#define APPLICATION_HPP

class Application {
private:
    sf::RenderWindow *window;

public:
    Application();
    ~Application();    

    void init_window(int w, int h);

    void menu();
};


#endif
