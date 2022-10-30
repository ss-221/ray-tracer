#ifndef UTILS_H
#define UTILS_H

#include <cppLogger.h>
#include <cmath>
#include <limits>
#include <memory>
#include <random>


#define ERRORMSG(...) cppLogger::Logger::ERRORMSG(__VA_ARGS__)
#define INFOMSG(...)  cppLogger::Logger::INFOMSG(__VA_ARGS__)
#define DEBUGMSG(...) cppLogger::Logger::DEBUGMSG(__VA_ARGS__)

using std::shared_ptr;
using std::make_shared;
using std::sqrt;

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double PI = 3.1415926535897932385;
constexpr double aspectRatio = 16.0 / 9.0;

inline double randomDouble() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}

inline double randomDouble(double min, double max) {
    return min + (max - min) * randomDouble();
}

#include <ray.h>
#include <vec3.h>

#endif // !UTILS_H
