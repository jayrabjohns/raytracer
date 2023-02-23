#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "../utils/math_utils.hpp"

class Vector3 {
public:
  double values[3];

public:
  Vector3();
  Vector3(double x, double y, double z);

  double x() const;
  double y() const;
  double z() const;

  double length() const;
  double length_sqr() const;
  Vector3 normalise() const;
  bool is_near_zero() const;
  Vector3 reflect(const Vector3& normal) const;
  Vector3 refract(const Vector3& normal, double refractiveRatio) const;

  double operator[](int i) const;
  Vector3 operator-() const;
  Vector3& operator+=(const Vector3& vec3);
  Vector3& operator*=(double t);
  Vector3& operator*=(const Vector3& vec3);
  Vector3& operator/=(double t);

  inline static Vector3 random_01() {
    return Vector3(random_double_01(), random_double_01(), random_double_01());
  }

  inline static Vector3 random(double min, double max) {
    return Vector3(random_double(min, max), random_double(min, max), random_double(min, max));
  }
};

inline std::ostream& operator<<(std::ostream& out, const Vector3& vec3) {
  return out << vec3.values[0] << ' ' << vec3.values[1] << ' ' << vec3.values[2];
}

inline Vector3 operator+(const Vector3& a, const Vector3& b) {
  return Vector3(
    a.values[0] + b.values[0],
    a.values[1] + b.values[1],
    a.values[2] + b.values[2]);
}

inline Vector3 operator-(const Vector3& a, const Vector3& b) {
  return Vector3(
    a.values[0] - b.values[0],
    a.values[1] - b.values[1],
    a.values[2] - b.values[2]);
}

inline Vector3 operator*(const Vector3& a, const Vector3& b) {
  return Vector3(
    a.values[0] * b.values[0],
    a.values[1] * b.values[1],
    a.values[2] * b.values[2]);
}

inline Vector3 operator*(double scalar, const Vector3& vec3) {
  return Vector3(
    scalar * vec3.values[0],
    scalar * vec3.values[1],
    scalar * vec3.values[2]);
}

inline Vector3 operator*(const Vector3& vec3, const double scalar) {
  return scalar * vec3;
}

inline Vector3 operator/(Vector3 vec3, const double scalar) {
  return (1 / scalar) * vec3;
}

inline double dot(const Vector3& a, const Vector3& b) {
  return a.values[0] * b.values[0] + a.values[1] * b.values[1] + a.values[2] * b.values[2];
}

inline Vector3 cross(const Vector3& a, const Vector3& b) {
  return Vector3(
    a.values[1] * b.values[2] - a.values[2] * b.values[1],
    a.values[2] * b.values[0] - a.values[0] * b.values[2],
    a.values[0] * b.values[1] - a.values[1] * b.values[0]);
}

inline Vector3 normalise(const Vector3 vec3) {
  return vec3 / vec3.length();
}

using Point3 = Vector3; // 3D Point
using Colour = Vector3; // RGB Colour
#endif
