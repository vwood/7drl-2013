#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <math.h>
#include "random.hpp"
#include "dvector.hpp"
#include "drawing.hpp"
#include "parse.hpp"
#include "map.hpp"
#include "map_object.hpp"
#include "poisson.hpp"
#include "test_units.hpp"

using namespace std;

const double epsilon = 0.00001;

bool Test_Units::result = true;

void Test_Units::test_random() {
    Random r1, r2;
    r1.set_seed(100);
    r2.set_seed(100);

    if (r1.get_seed() != 100) {
        cerr << "Random seed is incorrect after being set!" << endl;
        result = false;
    }

    if (r1.get_int(0,10) != r2.get_int(0,10) ||
        r1.get_int(0,10) != r2.get_int(0,10) ||
        r1.get_int(0,10) != r2.get_int(0,10) ||
        r1.get_int(0,10) != r2.get_int(0,10)) {
        cerr << "Same integer not returned from same seed" << endl;
        result = false;
    }

    if (r1.get_seed() != r2.get_seed()) {
        cerr << "Seeds not the same after same sequence!" << endl;
        result = false;
    }

    r1.set_seed(100);
    r2.set_seed(100);
    
    if (fabs(r1.get_double(0,10) - r2.get_double(0,10)) > epsilon ||
        fabs(r1.get_double(0,10) - r2.get_double(0,10)) > epsilon ||
        fabs(r1.get_double(0,10) - r2.get_double(0,10)) > epsilon ||
        fabs(r1.get_double(0,10) - r2.get_double(0,10)) > epsilon) {
        cerr << "Same double not returned from same seed" << endl;
        result = false;
    }
}

void Test_Units::test_poisson() {
    Poisson p;
    Random r;
    r.set_seed(100);
    
    p.generate(r, 100, 100, 10, 10, 10);

    if (p.get_x().size() == 0) {
        cerr << "Poisson generated empty list" << endl;
        result = false;
    }

    if (p.get_x().size() != p.get_y().size()) {
        cerr << "Poisson generated different length x & y lists" << endl;
        result = false;
    }
}

void Test_Units::run() {
    result = true;
    
    test_random();
    test_poisson();

    if (result) {
        cout << "All tests pass successfully." << endl;
    } else {
        cout << "Tests failed." << endl;
    }
}
