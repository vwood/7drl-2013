#include <iostream>
#include <vector>
#include "random.hpp"
#include "drawing.hpp"
#include "dvector.hpp"

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
    v.set_zero();
    print_vector(v.get());
    v.add_sin(10.0, 0.0, 1.0);
    print_vector(v.get());
}

int main() {
    test_dvector();
    
    return 0;
}
