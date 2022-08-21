#include "vec3.hpp"

Vec3::Vec3() : values{ 0.0, 0.0, 0.0 } {}
Vec3::Vec3(const double x, const double y, const double z) : values{ x, y, z } {}

double Vec3::x() const { return values[0]; }
double Vec3::y() const { return values[1]; }
double Vec3::z() const { return values[2]; }

double Vec3::length() const { return std::sqrt(Vec3::lengthSqr()); }
double Vec3::lengthSqr() const { return values[0] * values[0] + values[1] * values[1] + values[2] * values[2]; }

Vec3 Vec3::Normalised() const
{
	double len = length();
	return Vec3(
		values[0] / len,
		values[1] / len,
		values[2] / len);
}

bool Vec3::isNearZero() const
{
	const double tolerance = 1e-8;
	return (fabs(values[0] < tolerance) 
		&& fabs(values[1] < tolerance) 
		&& fabs(values[2] < tolerance));
}

Vec3 Vec3::reflect(const Vec3& normal)
{
	return (* this) - 2.0 * dot((* this), normal) * normal;
}

double Vec3::operator[](const int i) const { return values[i]; }
double& Vec3::operator[](const int i) { return values[i]; }
Vec3 Vec3::operator-() const { return Vec3::Vec3(-values[0], -values[1], -values[2]); }

Vec3& Vec3::operator+=(const Vec3& vec3)
{
	values[0] += vec3.values[0];
	values[1] += vec3.values[1];
	values[2] += vec3.values[2];
	return *this;
}

Vec3& Vec3::operator*=(const double t)
{
	values[0] *= t;
	values[1] *= t;
	values[2] *= t;
	return *this;
}

Vec3& Vec3::operator*=(const Vec3& vec3)
{
	values[0] *= vec3.values[0];
	values[1] *= vec3.values[1];
	values[2] *= vec3.values[2];
	return *this;
}

Vec3& Vec3::operator/=(const double t) 
{ 
	values[0] /= t;
	values[1] /= t;
	values[2] /= t;
	return *this;
}
