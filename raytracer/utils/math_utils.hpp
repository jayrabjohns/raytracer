#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <cmath>
#include <limits>
#include <random>

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

static std::mt19937 rng;

// Functions
inline double DegToRad(double degrees) { return degrees * pi / 180.0; }

inline double RandomDouble01()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    return distribution(rng);
}

inline double RandomDouble(double min, double max)
{
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(rng);
}

inline double Clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}
#endif