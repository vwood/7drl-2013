#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "random.hpp"
#include "drawing.hpp"
#include "dvector.hpp"
#include "parse.hpp"

using namespace std;

void print_vector(const vector<double> &v) {
    bool first = true;
    for (vector<double>::const_iterator it = v.begin(); it != v.end(); it++) {
        if (first) {
            first = false;
        } else {
            cout << ", ";
        }
        cout << *it;
    }
    cout << endl;
}

void test_random() {
    Random r;

    r.set_seed(100);

    cout << r.get_int(10, 20) << ", ";
    cout << r.get_int(10, 20) << ", ";
    cout << r.get_double(10, 20) << ", ";
    cout << r.get_double(10, 20) << endl;

    r.set_seed(100);

    cout << r.get_int(10, 20) << ", ";
    cout << r.get_int(10, 20) << ", ";
    cout << r.get_double(10, 20) << ", ";
    cout << r.get_double(10, 20) << endl;
}

void test_vector() {
    Random r;
    r.set_seed(100);

    vector<double> *noise = generate_noise(10, &r, 10.0);

    print_vector(*noise);
}

void test_dvector() {
    Random r;
    r.set_seed(100);

    DVector v(20);
    print_vector(v.get());
    v.add_noise(r, 10.0);
    print_vector(v.get());
    v.clear();
    print_vector(v.get());
    v.add_sin(10.0, 0.0, 1.0);
    print_vector(v.get());
}

void set_vertexarray_to_dvectors(sf::VertexArray &va, int n, DVector &xs, DVector &ys) {
	int i;
	vector<double>::const_iterator xit, yit;

	for (i = 0, xit = xs.get().begin(), yit = ys.get().begin();
		 i < n && xit != xs.get().end() && yit != ys.get().end();
		 i++, xit++, yit++) {
		va[i].position = sf::Vector2f(*xit, *yit);
	}
}

void test_circle() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(400, 400), "Circle Test");
    Random r;

	DVector xs(20), ys(20);
    xs.add_sin(50.0, 0.0, 2.0);
    ys.add_cos(50.0, 0.0, 2.0);
	xs.add(200.0);
	ys.add(200.0);

	sf::VertexArray lines(sf::LinesStrip, 20);
	set_vertexarray_to_dvectors(lines, 20, xs, ys);

	sf::Event event;

	window.clear(sf::Color::Black);

	while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
			}
		}
		window.clear(sf::Color::Black);
		window.draw(lines);
		window.display();
	}
}

void test_wave() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(200, 200), "Wave Test");
    Random r;

	int n = 24 + 1; // NOTE: Need power of two + 1 for the fine peaks

	vector<sf::VertexArray> waves;

	for (int i = 0; i < 6; i++) {
		DVector xs(n), ys(n);
		xs.add_linear(20.0 + (i % 2) * 20.0, 160.0 + (i % 2) * 20);
		//xs.add_noise(r, 2.0);
		ys.add_sin(16.0, 0.5, 4.5);
		ys.map_abs();
		//ys.add_noise(r, 2.0);
		ys.add(20.0 + i * 30.0);
	
		sf::VertexArray lines(sf::LinesStrip, n);
		set_vertexarray_to_dvectors(lines, n, xs, ys);

		waves.push_back(lines);
	}

	sf::Event event;

	window.clear(sf::Color::Black);

	while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
			}
		}
		window.clear(sf::Color::Black);
		for (vector<sf::VertexArray>::iterator it = waves.begin(); it != waves.end(); it++) {
			window.draw(*it);
		}
		window.display();
	}
}

void test_mnt() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(200, 200), "Wave Test");
    Random r;

	int n = 12;

    int x = 20, y = 20, w = 160, h = 160;
    
	DVector mntlx(n), mntly(n);
    DVector mntmx(n), mntmy(n);
    DVector mntrx(n), mntry(n);

    mntlx.add_linear(x, x+w/2);
    mntlx.add_noise(r, 4.0);
    mntly.add_linear(y+h, y);
    mntly.add_noise(r, 4.0);

    mntmx.add_linear(x+w/2, x+w*r.get_double(0.7, 0.9));
    mntmx.add_noise(r, 4.0);
    mntmy.add_linear(y, y+h*r.get_double(1.1, 1.2));
    mntmy.add_noise(r, 4.0);

    mntrx.add_linear(x+w/2, x+w);
    mntrx.add_noise(r, 4.0);
    mntry.add_linear(y, y+h);
    mntry.add_noise(r, 4.0);
        
	sf::VertexArray mntl(sf::LinesStrip, n), mntm(sf::LinesStrip, n), mntr(sf::LinesStrip, n);

    set_vertexarray_to_dvectors(mntl, n, mntlx, mntly);
    set_vertexarray_to_dvectors(mntm, n, mntmx, mntmy);
    set_vertexarray_to_dvectors(mntr, n, mntrx, mntry);

	sf::Event event;

	window.clear(sf::Color::Black);

	while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
			}
		}
		window.clear(sf::Color::Black);
        window.draw(mntl);
        window.draw(mntm);
        window.draw(mntr);
		window.display();
	}
}

int main() {
//    test_wave();

//    parse("resources/test.txt");

    test_mnt();

    return 0;
}
