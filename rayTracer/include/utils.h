#ifndef UTILS_H
#define UTILS_H

#include <cppLogger.h>
#include <cmath>
#include <limits>
#include <memory>
#include <random>
#include <fstream>

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double PI = 3.1415926535897932385;

inline double randomDouble() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double randomDouble(double min, double max) {
    return min + (max - min) * randomDouble();
}

inline double degreesToRadians(double degrees)
{
    return degrees * PI / 180.0;
}

#endif // !UTILS_H
