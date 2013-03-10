#ifndef RANDOM_HPP
#define RANDOM_HPP

class Random {
private:
    unsigned int seed;
    
public:
    Random();

    void set_seed(unsigned int seed);
    unsigned int get_seed();
    
    double get_double(double low, double high);
    int get_int(int low, int high);
};

#endif
