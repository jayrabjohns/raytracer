#include "vec3.hpp"

Vector3::Vector3(): Vector3(0.0, 0.0, 0.0) {}
Vector3::Vector3(const double x, const double y, const double z): values{ x, y, z } {}

double Vector3::x() const { return values[0]; }
double Vector3::y() const { return values[1]; }
double Vector3::z() const { return values[2]; }

double Vector3::length() const {
  return std::sqrt(Vector3::length_sqr());
}

double Vector3::length_sqr() const {
  return
    values[0] * values[0] +
    values[1] * values[1] +
    values[2] * values[2];
}

Vector3 Vector3::normalise() const {
  double len = length();
  return Vector3(
    values[0] / len,
    values[1] / len,
    values[2] / len);
}

bool Vector3::is_near_zero() const {
  const double tolerance = 1e-8;
  return (
    fabs(values[0] < tolerance) &&
    fabs(values[1] < tolerance) &&
    fabs(values[2] < tolerance));
}

Vector3 Vector3::reflect(const Vector3& normal) {
  return (*this) - 2.0 * dot((*this), normal) * normal;
}

Vector3 Vector3::refract(const Vector3& normal, const double refractive_ratio) {
  double cos_theta = fmin(dot(-(*this), normal), 1.0);
  Vector3 refracted_perpendicular = refractive_ratio * ((*this) + cos_theta * normal);
  Vector3 refractive_parallel = -sqrt(fabs(1.0 - refracted_perpendicular.length_sqr())) * normal;
  return refracted_perpendicular + refractive_parallel;
}

double Vector3::operator[](const int i) const {
  return values[i];
}

double& Vector3::operator[](const int i) {
  return values[i];
}

Vector3 Vector3::operator-() const {
  return Vector3(-values[0], -values[1], -values[2]);
}

Vector3& Vector3::operator+=(const Vector3& vec3) {
  values[0] += vec3.values[0];
  values[1] += vec3.values[1];
  values[2] += vec3.values[2];
  return *this;
}

Vector3& Vector3::operator*=(const double t) {
  values[0] *= t;
  values[1] *= t;
  values[2] *= t;
  return *this;
}

Vector3& Vector3::operator*=(const Vector3& vec3) {
  values[0] *= vec3.values[0];
  values[1] *= vec3.values[1];
  values[2] *= vec3.values[2];
  return *this;
}

Vector3& Vector3::operator/=(const double t) {
  values[0] /= t;
  values[1] /= t;
  values[2] /= t;
  return *this;
}
