#ifndef UTILLITIES_H
#define UTILLITIES_H

#include <iostream>
#include <random>

inline float random_float() {
    static std::uniform_real_distribution<float> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
inline float random_float(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min)*random_float();
}



#endif
