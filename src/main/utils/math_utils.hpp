#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <cmath>
#include <limits>
#include <cstdlib>

#include "../geometry/vec3.hpp"

constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

inline double deg_to_rad(double degrees) {
  return degrees * pi / 180.0;
}

inline double random_double_01() {
  return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
  return min + (max - min) * random_double_01();
}

inline double clamp(double x, double min, double max) {
  if (x < min) return min;
  if (x > max) return max;
  return x;
}

inline double clamp_01(double x) {
  return clamp(x, 0.0, 1.0);
}

inline bool in_bounds_inclusive(const double val, const double min, const double max) {
  return min <= val && val <= max;
}
#endif
