#include "vec3.hpp"

Vec3::Vec3() : Vals{ 0.0, 0.0, 0.0 } {}
Vec3::Vec3(const double x, const double y, const double z) : Vals{ x, y, z } {}

double Vec3::x() const { return Vals[0]; }
double Vec3::y() const { return Vals[1]; }
double Vec3::z() const { return Vals[2]; }

double Vec3::length() const { return std::sqrt(Vec3::lengthSqr()); }
double Vec3::lengthSqr() const { return Vals[0] * Vals[0] + Vals[1] * Vals[1] + Vals[2] * Vals[2]; }

double Vec3::operator[](const int i) const { return Vals[i]; }
double& Vec3::operator[](const int i) { return Vals[i]; }
Vec3 Vec3::operator-() const { return Vec3::Vec3(-Vals[0], -Vals[1], -Vals[2]); }

Vec3& Vec3::operator+=(const Vec3& vec3)
{
	Vals[0] += vec3.Vals[0];
	Vals[1] += vec3.Vals[1];
	Vals[2] += vec3.Vals[2];
	return *this;
}

Vec3& Vec3::operator*=(const double t)
{
	Vals[0] *= t;
	Vals[1] *= t;
	Vals[2] *= t;
	return *this;
}

Vec3& Vec3::operator/=(const double t) { return *this *= 1 / t; }
