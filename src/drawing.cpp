#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "random.hpp"
#include "dvector.hpp"
#include "map_color.hpp"
#include "drawing.hpp"

using namespace std;

Drawing::Drawing() {}

/*
 * Delete all items in the vector.
 */
Drawing::~Drawing() {
    for (vector<sf::VertexArray *>::iterator vit=v.begin(); vit != v.end(); vit++) {
        delete *vit;
    }
}

void Drawing::draw(sf::RenderWindow &r, double x, double y) {
    sf::Transform t;
    t.translate(x, y);
    sf::RenderStates rs(t);

    for (vector<sf::VertexArray *>::iterator it = v.begin(); it != v.end(); it++) {
        r.draw(**it, rs);
    }
}

/*
 * Sets points in a VertexArray to the values in a pair of DVectors
 *
 * offset is the offset of the points in the VertexArray (so you can build one from multiple DVectors)
 * n is the number of points (in case the VertexArray is smaller than the DVectors)
 */
void set_vertexarray_to_dvectors(sf::VertexArray &va, int offset, int n, DVector &xs, DVector &ys) {
	int i;
	vector<double>::const_iterator xit, yit;

	for (i = 0, xit = xs.get().begin(), yit = ys.get().begin();
		 i < n && xit != xs.get().end() && yit != ys.get().end();
		 i++, xit++, yit++) {
		va[i + offset].position = sf::Vector2f(*xit, *yit);
	}
}

/*
 * Sets points in a VertexArray to the color specified
 * 
 * offset is the offset to begin at
 * n is the number of points to set
 */
void set_vertexarray_to_color(sf::VertexArray &va, int offset, int n, sf::Color c) {
	int i;
	vector<double>::const_iterator xit, yit;

	for (i = 0; i < n; i++) {
		va[i + offset].color = c;
	}
}

/*
 * Factory function for generating mountains
 */
Drawing *Drawing::new_mountain(Random &r, double size) {
	int n = 12;

    int height = r.get_int(size * 1/2, size * 2/3);
    int x = -(size/2), y = -height, w = size, h = height;
    
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

    sf::VertexArray *mntl, *mntm, *mntr, *mntp1, *mntp2;
    mntl = new sf::VertexArray(sf::LinesStrip, n);
    mntm = new sf::VertexArray(sf::LinesStrip, n);
    mntr = new sf::VertexArray(sf::LinesStrip, n);
    mntp1 = new sf::VertexArray(sf::TrianglesFan, n * 2 + 1);
    mntp2 = new sf::VertexArray(sf::TrianglesFan, n * 2 + 1);

    set_vertexarray_to_dvectors(*mntl, 0, n, mntlx, mntly);
    set_vertexarray_to_dvectors(*mntm, 0, n, mntmx, mntmy);
    set_vertexarray_to_dvectors(*mntr, 0, n, mntrx, mntry);

    set_vertexarray_to_color(*mntl, 0, n, Map_Color::outlines);
    set_vertexarray_to_color(*mntm, 0, n, Map_Color::outlines);
    set_vertexarray_to_color(*mntr, 0, n, Map_Color::outlines);
    set_vertexarray_to_color(*mntp1, 0, n*2 + 1, Map_Color::mountain_back);
    set_vertexarray_to_color(*mntp2, 0, n*2 + 1, Map_Color::mountain_front);
    
    (*mntp1)[0].position = sf::Vector2f(x+w/2, y+h*1.1);
    set_vertexarray_to_dvectors(*mntp1, 1, n, mntlx, mntly);
    set_vertexarray_to_dvectors(*mntp1, n, n, mntrx, mntry);
    (*mntp1)[n*2].position = sf::Vector2f(mntmx.get()[n-1], mntmy.get()[n-1]);

    (*mntp2)[0].position = sf::Vector2f(x+w/2, y+h*1.1);
    set_vertexarray_to_dvectors(*mntp2, 1, n, mntlx, mntly);
    set_vertexarray_to_dvectors(*mntp2, n, n, mntmx, mntmy);
    (*mntp2)[n*2].position = sf::Vector2f(mntmx.get()[n-1], mntmy.get()[n-1]);

    Drawing *result = new Drawing();
    result->v.push_back(mntp1);
    result->v.push_back(mntp2);
    result->v.push_back(mntl);
    result->v.push_back(mntm);
    result->v.push_back(mntr);
    
    return result;
}

Drawing *Drawing::new_tree(Random &r, double size) {
	int n = 14;

    int height = r.get_int(size * 1/2, size * 2/3);
    int x = -(size/2), y = -height, w = size, h = height;
    
	DVector leavesx(n), leavesy(n);
    DVector trunkx(4), trunky(4);

	trunkx.set(0, x + w/2 - size/16);
    trunky.set(0, y + height);
    trunkx.set(1, x + w/2 - size/32);
    trunky.set(1, y + height * 4 / 5);
    trunkx.set(2, x + w/2 + size/32);
    trunky.set(2, y + height * 4 / 5);
    trunkx.set(3, x + w/2 + size/16);
    trunky.set(3, y + height);
    
    leavesx.add_sin(size / 3, 0.0, 2.0);
    leavesx.add_noise(r, -3.0, 3.0);
    leavesx.add(x + w/2);
	leavesy.add_cos(height / 2, 0.0, 2.0);
    leavesy.add_noise(r, -3.0, 3.0);
    leavesy.add(y + h*2/5);

    sf::VertexArray *leaves_line, *trunk_line, *leaves_poly, *trunk_poly;
    leaves_line = new sf::VertexArray(sf::LinesStrip, n + 1);
    trunk_line = new sf::VertexArray(sf::LinesStrip, 4);
    leaves_poly = new sf::VertexArray(sf::TrianglesFan, n);
    trunk_poly = new sf::VertexArray(sf::TrianglesFan, 4);

    set_vertexarray_to_dvectors(*leaves_line, 0, n, leavesx, leavesy);
    (*leaves_line)[n].position = (*leaves_line)[0].position; // close the loop
    set_vertexarray_to_dvectors(*trunk_line, 0, 4, trunkx, trunky);
    set_vertexarray_to_dvectors(*leaves_poly, 0, n, leavesx, leavesy);
    set_vertexarray_to_dvectors(*trunk_poly, 0, 4, trunkx, trunky);

    set_vertexarray_to_color(*leaves_line, 0, n + 1, Map_Color::outlines);
    set_vertexarray_to_color(*trunk_line, 0, 4, Map_Color::outlines);
    set_vertexarray_to_color(*leaves_poly, 0, n, Map_Color::tree_leaves);
    set_vertexarray_to_color(*trunk_poly, 0, 4, Map_Color::tree_trunk);
    
    Drawing *result = new Drawing();
    result->v.push_back(leaves_poly);
    result->v.push_back(leaves_line);
    result->v.push_back(trunk_poly);
    result->v.push_back(trunk_line);
    return result;
}

Drawing *Drawing::new_hill(Random &r, double size) {
	int n = 12;

    int height = r.get_int(size/5, size/4);
    int x = -(size/2), y = -height, w = size, h = height;
    
	DVector hill1x(n), hill1y(n);
    DVector hill2x(n), hill2y(n);

    if (r.get_int(0, 2) == 1) {
        hill1x.add_linear(x, x+w*2/3);
        hill2x.add_linear(x+w/3, x+w);
    } else {
        hill1x.add_linear(x+w/3, x+w);
        hill2x.add_linear(x, x+w*2/3);
    }
        
    hill1y.add_sin(h, 1.0, 2.0);
    hill1y.add(y+h*7/8);
    hill2y.add_sin(h, 1.0, 2.0);
    hill2y.add(y+h);

    sf::VertexArray *hill1l, *hill2l, *hill1p, *hill2p;
    hill1l = new sf::VertexArray(sf::LinesStrip, n);
    hill2l = new sf::VertexArray(sf::LinesStrip, n);
    hill1p = new sf::VertexArray(sf::TrianglesFan, n);
    hill2p = new sf::VertexArray(sf::TrianglesFan, n);


    set_vertexarray_to_dvectors(*hill1l, 0, n, hill1x, hill1y);
    set_vertexarray_to_dvectors(*hill1p, 0, n, hill1x, hill1y);    
    set_vertexarray_to_dvectors(*hill2l, 0, n, hill2x, hill2y);
    set_vertexarray_to_dvectors(*hill2p, 0, n, hill2x, hill2y);    

    set_vertexarray_to_color(*hill1l, 0, n, Map_Color::outlines);
    set_vertexarray_to_color(*hill2l, 0, n, Map_Color::outlines);
    set_vertexarray_to_color(*hill1p, 0, n, Map_Color::hill_back);
    set_vertexarray_to_color(*hill2p, 0, n, Map_Color::hill_front);    
    
    Drawing *result = new Drawing();
    result->v.push_back(hill1p);
    result->v.push_back(hill1l);
    result->v.push_back(hill2p);
    result->v.push_back(hill2l);
    return result;
}

Drawing *Drawing::new_wave(Random &r, double size) {
	int n = 32 + 1;

    int height = r.get_int(size * 1/2, size * 2/3);
    int x = -(size/2), y = -height, w = size, h = height;
    
	DVector wavex(n), wavey(n);

    int wave_size = h/3;
    wavex.add_linear(x, x + w);
	wavey.add_cos(h / 3, 0.0, 4.0);
    wavey.map_abs();
    wavey.add(y+h - wave_size/2);

    sf::VertexArray *wave_line;
    wave_line = new sf::VertexArray(sf::LinesStrip, n);

    set_vertexarray_to_dvectors(*wave_line, 0, n, wavex, wavey);

    set_vertexarray_to_color(*wave_line, 0, n, Map_Color::wave);

    Drawing *result = new Drawing();
    result->v.push_back(wave_line);
    return result;
}

Drawing *Drawing::new_lake(Random &r, double size) {
	int n = 16;

    int height = r.get_int(size * 1/2, size * 2/3);
    int x = -(size/2), y = -height, w = size, h = height;
    
	DVector lakex(n), lakey(n);

    lakex.add_sin(w / 3, 0.0, 2.0);
	lakey.add_cos(h / 3, 0.0, 2.0);

    lakex.add_noise(r, -4.0, 4.0);
	lakey.add_noise(r, -4.0, 4.0);

    lakex.add(x);
    lakey.add(y);

    sf::VertexArray *lake;
    lake = new sf::VertexArray(sf::TrianglesFan, n);

    set_vertexarray_to_dvectors(*lake, 0, n, lakex, lakey);
    set_vertexarray_to_color(*lake, 0, n, Map_Color::lake);

    Drawing *result = new Drawing();
    result->v.push_back(lake);
    return result;
}


Drawing *Drawing::new_land(Random &r, double size) { return NULL; }

Drawing *Drawing::new_tower(Random &r, double size) { return NULL; }
Drawing *Drawing::new_keep(Random &r, double size) { return NULL; }
Drawing *Drawing::new_hut(Random &r, double size) { return NULL; }

Drawing *Drawing::new_shield(Random &r, double size) {
	int n = 7;
    int x = -(size/2), y = -(size/2), w = size, h = size;

	DVector shieldx(n+1), shieldy(n+1);

	shieldx.set(0, x);
    shieldy.set(0, y);
    shieldx.set(1, x);
    shieldy.set(1, y+h/2);
    shieldx.set(2, x+w/8);
    shieldy.set(2, y+h*7/8);
    shieldx.set(3, x+w/2);
    shieldy.set(3, y+h);
    shieldx.set(4, x+w*7/8);
    shieldy.set(4, y+h*7/8);
    shieldx.set(5, x+w);
    shieldy.set(5, y+h/2);
    shieldx.set(6, x+w);
    shieldy.set(6, y);
    shieldx.set(7, x);
    shieldy.set(7, y);

    sf::VertexArray *shield_line, *shield_poly;
    shield_line = new sf::VertexArray(sf::LinesStrip, n + 1);
    shield_poly = new sf::VertexArray(sf::TrianglesFan, n);

    set_vertexarray_to_dvectors(*shield_line, 0, n + 1, shieldx, shieldy);
    set_vertexarray_to_color(*shield_line, 0, n + 1, Map_Color::outlines); 
    set_vertexarray_to_dvectors(*shield_poly, 0, n, shieldx, shieldy);
    set_vertexarray_to_color(*shield_poly, 0, n, Map_Color::shield);

    Drawing *result = new Drawing();
    result->v.push_back(shield_poly);
    result->v.push_back(shield_line);
    return result;
}
