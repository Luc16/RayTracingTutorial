#ifndef RTTUTORIAL_H
#define RTTUTORIAL_H

#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include <chrono>


// Usings

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;


// Utility Functions

inline double clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline double degrees_to_radians(double degrees) {
    return degrees * pi / 180.0;
}

inline double random_double(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<double> dis_double;
    return dis_double(gen);
}

inline double random_double(double min, double max) {
    return min + random_double()*(max - min);
}

inline int random_int(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<int> dis_int(min, max);
    return dis_int(gen);
}


// Common Headers

#include "generals/ray.h"
#include "generals/vec3.h"

#endif //RTTUTORIAL_H
