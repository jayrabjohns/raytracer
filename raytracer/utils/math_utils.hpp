#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <cmath>
#include <limits>
#include <cstdlib>

#include "../geometry/vec3.hpp"

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Functions
inline double DegToRad(double degrees) { return degrees * pi / 180.0; }

inline double RandomDouble01()
{
    return rand() / (RAND_MAX + 1.0);
}

inline double RandomDouble(double min, double max)
{
    return min + (max - min) * RandomDouble01();
}

inline double Clamp(double x, double min, double max)
{
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

inline double Clamp01(double x)
{
    return Clamp(x, 0.0, 1.0);
}
#endif