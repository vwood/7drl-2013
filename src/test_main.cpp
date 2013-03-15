#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include "random.hpp"
#include "dvector.hpp"
#include "drawing.hpp"
#include "parse.hpp"
#include "map.hpp"
#include "map_object.hpp"
#include "poisson.hpp"

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

/*
 * Simple window loop, won't redraw (but fuck it, this is testing)
 */
void window_loop(sf::RenderWindow &window) {
	sf::Event event;
	while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
			} else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
				}
			}
            
		}
        sf::sleep(sf::seconds(0.1f));
	}
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

void test_dvector() {
    Random r;
    r.set_seed(100);

    DVector v(20);
    print_vector(v.get());
    v.add_noise(r, -10.0, 10.0);
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
    sf::RenderWindow window(sf::VideoMode(400, 400), "Circle Test");
    Random r;

	DVector xs(20), ys(20);
    xs.add_sin(50.0, 0.0, 2.0);
    ys.add_cos(50.0, 0.0, 2.0);
	xs.add(200.0);
	ys.add(200.0);

	sf::VertexArray lines(sf::LinesStrip, 20);
	set_vertexarray_to_dvectors(lines, 20, xs, ys);

	window.clear(sf::Color::Black);
	window.draw(lines);
	window.display();
	window_loop(window);
}

void test_wave() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Wave Test");
    Random r;

	int n = 24 + 1; // NOTE: Need power of two + 1 for the fine peaks

	vector<sf::VertexArray> waves;

	for (int i = 0; i < 6; i++) {
		DVector xs(n), ys(n);
		xs.add_linear(20.0 + (i % 2) * 20.0, 160.0 + (i % 2) * 20);
		//xs.add_noise(r, -2.0, 2.0);
		ys.add_sin(16.0, 0.5, 4.5);
		ys.map_abs();
		//ys.add_noise(r, -2.0, 2.0);
		ys.add(20.0 + i * 30.0);
	
		sf::VertexArray lines(sf::LinesStrip, n);
		set_vertexarray_to_dvectors(lines, n, xs, ys);

		waves.push_back(lines);
	}

	window.clear(sf::Color::Black);
	for (vector<sf::VertexArray>::iterator it = waves.begin(); it != waves.end(); it++) {
		window.draw(*it);
	}
	window.display();
	window_loop(window);
}

void test_mnt() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Wave Test");
    Random r;
	cout << r.get_seed() << endl;

	int n = 12;

    int x = 20, y = 60, w = 160, h = 120;
    
	DVector mntlx(n), mntly(n);
    DVector mntmx(n), mntmy(n);
    DVector mntrx(n), mntry(n);

    mntlx.add_linear(x, x+w/2);

	mntly.set(0, y+h);
	mntly.set(n-1, y);
	mntly.map_midpoint_displacement(r, 0.3, 0.7);
	
    mntmx.add_linear(x+w/2, x+w*r.get_double(0.7, 0.9));
	
	mntmy.set(0, y);
	mntmy.set(n-1, y+h*r.get_double(1.1, 1.2));
	mntmy.map_midpoint_displacement(r, 0.3, 0.7);
	
    mntrx.add_linear(x+w/2, x+w);

	mntry.set(0, y);
	mntry.set(n-1, y+h);
	mntry.map_midpoint_displacement(r, 0.3, 0.7);
	
	sf::VertexArray mntl(sf::LinesStrip, n), mntm(sf::LinesStrip, n), mntr(sf::LinesStrip, n);

    set_vertexarray_to_dvectors(mntl, n, mntlx, mntly);
    set_vertexarray_to_dvectors(mntm, n, mntmx, mntmy);
    set_vertexarray_to_dvectors(mntr, n, mntrx, mntry);

	window.clear(sf::Color::Black);
	window.draw(mntl);
	window.draw(mntm);
	window.draw(mntr);
	window.display();

	window_loop(window);
}

void test_poisson() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Wave Test");
    Random r;
	Poisson p;

	p.generate(r, 200, 200, 30, 10, 100);

	window.clear(sf::Color::Black);
	sf::CircleShape cs(2, 4);
	for (vector<double>::const_iterator xit = p.get_x().begin(), yit = p.get_y().begin();
		 xit != p.get_x().end() && yit != p.get_y().end(); xit++, yit++) {
		cs.setPosition(*xit, *yit);
		window.draw(cs);
	}
	window.display();

	window_loop(window);
}

void test_poisson2(int w, int h, int radius) {
    sf::RenderWindow window(sf::VideoMode(w, h), "Wave Test");
    Random r;
	Poisson p;
    
    p.generate(r, w, h, radius, 40);
    
	window.clear(sf::Color::Black);
	sf::CircleShape cs(radius, 8);
	for (vector<double>::const_iterator xit = p.get_x().begin(), yit = p.get_y().begin();
		 xit != p.get_x().end() && yit != p.get_y().end(); xit++, yit++) {
		cs.setPosition(*xit, *yit);
		window.draw(cs);
	}
	window.display();

    cerr << p.get_x().size() << endl;

	window_loop(window);
}



void test_drawing() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Wave Test");
    Random r;
    Drawing *mnt = Drawing::new_mountain(r, 100);
    Drawing *tree = Drawing::new_tree(r, 80);
    Drawing *wave = Drawing::new_wave(r, 80);

    window.clear(sf::Color(128, 128, 128, 0));
	mnt->draw(window, 100, 180);
	tree->draw(window, 110, 100);
	wave->draw(window, 100, 40);

	sf::CircleShape cs(2, 4);
    cs.setPosition(100, 40);
    window.draw(cs);

    
    window.display();
    window_loop(window);
}

void test_spline() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Wave Test");
    Random r;

    window.clear(sf::Color(128, 128, 128, 0));

    DVector s(6), splinex(26), spliney(26);

    s.set(0, 10.0);
    s.set(1, 90.0);
    s.set(2, 70.0);
    s.set(3, 130.0);
    s.set(4, 110.0);
    s.set(5, 190.0);
    splinex.set_to_spline(&s);
    s.set(0, 180.0);
    s.set(1, 170.0);
    s.set(2, 60.0);
    s.set(3, 60.0);
    s.set(4, 170.0);
    s.set(5, 180.0);
    spliney.set_to_spline(&s);

    sf::VertexArray va(sf::LinesStrip, 26);
    set_vertexarray_to_dvectors(va, 26, splinex, spliney);
    window.draw(va);
    window.display();
    window_loop(window);
}

void test_shield() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Wave Test");
    Random r;

    window.clear(sf::Color(128, 128, 128, 0));

    Drawing *shield = Drawing::new_shield(r, 100);
	shield->draw(window, 100, 100);
    window.display();
    window_loop(window);
}

void test_map() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Map Test");
    Random r;

    window.clear(sf::Color(128, 128, 128, 0));

    Map m(200, 200, 20, 20);
    m.fill_tiles_randomly(r);
	m.draw(window, 0, 0, 200, 200);
    window.display();
    window_loop(window);
}

void test_lake() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Map Test");
    Random r;

    window.clear(sf::Color(128, 128, 128, 0));
    Drawing * lake = Drawing::new_lake(r, 100);
	lake->draw(window, 100, 100);
    window.display();
    window_loop(window);
}

void test_island_gen() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "Map Test");
    Random r;

    window.clear(sf::Color(128, 128, 128, 0));
    int n = 32;
    DVector xs(n), ys(n), noise(n);
    noise.add_noise(r, 0.3, 1.3);
    noise.map_wrapped_midpoint_displacement(r, -0.2, 1.2);    
    xs.add_sin(1, 0.0, 2.0);
    ys.add_cos(1, 0.0, 2.0);
    xs.multiply(&noise);
    ys.multiply(&noise);
    xs.multiply(80);
    ys.multiply(80);
    xs.add(100);
    ys.add(100);    
    sf::VertexArray va(sf::TrianglesFan, n);
    set_vertexarray_to_dvectors(va, n, xs, ys);
    window.draw(va);
    window.display();
    window_loop(window);
}

void test_map_objects(int w, int h) {
    sf::RenderWindow window(sf::VideoMode(w, h), "Map Test");
    Random r;
    window.clear(sf::Color(128, 128, 128, 0));
    Map m(w, h, 40, 40);
    m.fill_tiles_randomly(r);
    m.fill_objects_randomly(r);
    m.draw(window, 0, 0, w, h);
    window.display();
    window_loop(window);
}

int main() {
//    test_wave();
//    parse("resources/test.txt");
//    test_mnt();
//    test_poisson();
    test_poisson2(400, 400, 28.28);
    test_drawing();
//    test_spline();
//    test_shield();
//    test_map();
//    test_lake();
//    test_island_gen();
    test_map_objects(400, 400);
    return 0;
}
