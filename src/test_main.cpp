#include <iostream>
#include <vector>
#include "random.hpp"
#include "drawing.hpp"

using namespace std;

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


void print_vector(vector<double> &v) {
    for (vector<double>::iterator it = v.begin(); it != v.end(); it++) {
        cout << *it << endl;
    }
}


int main() {
    Random r;
    r.set_seed(100);
    
    vector<double> *noise = generate_noise(10, &r, 10.0);

    print_vector(*noise);
    cout << noise << endl;
    
    return 0;
}
