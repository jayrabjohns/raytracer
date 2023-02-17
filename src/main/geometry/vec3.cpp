#include "vec3.hpp"

Vector3::Vector3() : Vector3(0.0, 0.0, 0.0) {}
Vector3::Vector3(const double x, const double y, const double z) : values{ x, y, z } {}

double Vector3::x() const { return values[0]; }
double Vector3::y() const { return values[1]; }
double Vector3::z() const { return values[2]; }

double Vector3::length() const { return std::sqrt(Vector3::lengthSqr()); }
double Vector3::lengthSqr() const { return values[0] * values[0] + values[1] * values[1] + values[2] * values[2]; }

Vector3 Vector3::Normalised() const
{
	double len = length();
	return Vector3(
		values[0] / len,
		values[1] / len,
		values[2] / len);
}

bool Vector3::isNearZero() const
{
	const double tolerance = 1e-8;
	return (fabs(values[0] < tolerance) 
		&& fabs(values[1] < tolerance) 
		&& fabs(values[2] < tolerance));
}

Vector3 Vector3::reflect(const Vector3& normal)
{
	return (* this) - 2.0 * dot((* this), normal) * normal;
}

Vector3 Vector3::refract(const Vector3& normal, const double refractiveRatio)
{
	double cosTheta = fmin(dot(-(* this), normal), 1.0);
	Vector3 refractedPerpendicular = refractiveRatio * ((*this) + cosTheta * normal);
	Vector3 refractiveParallel = -sqrt(fabs(1.0 - refractedPerpendicular.lengthSqr())) * normal;
	return refractedPerpendicular + refractiveParallel;
}

double Vector3::operator[](const int i) const { return values[i]; }
double& Vector3::operator[](const int i) { return values[i]; }
Vector3 Vector3::operator-() const { return Vector3(-values[0], -values[1], -values[2]); }

Vector3& Vector3::operator+=(const Vector3& vec3)
{
	values[0] += vec3.values[0];
	values[1] += vec3.values[1];
	values[2] += vec3.values[2];
	return *this;
}

Vector3& Vector3::operator*=(const double t)
{
	values[0] *= t;
	values[1] *= t;
	values[2] *= t;
	return *this;
}

Vector3& Vector3::operator*=(const Vector3& vec3)
{
	values[0] *= vec3.values[0];
	values[1] *= vec3.values[1];
	values[2] *= vec3.values[2];
	return *this;
}

Vector3& Vector3::operator/=(const double t) 
{ 
	values[0] /= t;
	values[1] /= t;
	values[2] /= t;
	return *this;
}
