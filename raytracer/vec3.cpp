#include "vec3.h"

vec3::vec3() : vals{ 0.0, 0.0, 0.0 } {}
vec3::vec3(const double x, const double y, const double z) : vals{ x, y, z } {}

double vec3::x() const { return vals[0]; }
double vec3::y() const { return vals[1]; }
double vec3::z() const { return vals[2]; }

double vec3::length() const { return std::sqrt(vec3::lengthSqr()); }
double vec3::lengthSqr() const { return vals[0] * vals[0] + vals[1] * vals[1] + vals[2] * vals[2]; }

double vec3::operator[](const int i) const { return vals[i]; }
double& vec3::operator[](const int i) { return vals[i]; }
vec3 vec3::operator-() const { return vec3::vec3(-vals[0], -vals[1], -vals[2]); }

vec3& vec3::operator+=(const vec3& vec3)
{
	vals[0] += vec3.vals[0];
	vals[1] += vec3.vals[1];
	vals[2] += vec3.vals[2];
	return *this;
}

vec3& vec3::operator*=(const double t)
{
	vals[0] *= t;
	vals[1] *= t;
	vals[2] *= t;
	return *this;
}

vec3& vec3::operator/=(const double t) { return *this *= 1 / t; }
