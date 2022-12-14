#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "../utils/math_utils.hpp"

class Vector3 
{
public:
	double values[3];

public:
	Vector3();
	Vector3(const double x, const double y, const double z);

	double x() const;
	double y() const;
	double z() const;

	double length() const;
	double lengthSqr() const;
	Vector3 Normalised() const;
	bool isNearZero() const;
	Vector3 reflect(const Vector3& normal);
	Vector3 refract(const Vector3& normal, const double refractiveRatio);

	double operator[](const int i) const;
	double& operator[](const int i);
	Vector3 operator-() const;
	Vector3& operator+=(const Vector3& vec3);
	Vector3& operator*=(const double t);
	Vector3& operator*=(const Vector3& vec3);
	Vector3& operator/=(const double t);

	inline static Vector3 Random01() { return Vector3(RandomDouble01(), RandomDouble01(), RandomDouble01()); }
	inline static Vector3 Random(double min, double max) { return Vector3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max)); }
};

inline std::ostream& operator<<(std::ostream& out, const Vector3& vec3) { return out << vec3.values[0] << ' ' << vec3.values[1] << ' ' << vec3.values[2]; }

inline Vector3 operator+(const Vector3& a, const Vector3& b) 
{
	return Vector3(
		a.values[0] + b.values[0],
		a.values[1] + b.values[1],
		a.values[2] + b.values[2]);
}

inline Vector3 operator-(const Vector3& a, const Vector3& b) 
{
	return Vector3(
		a.values[0] - b.values[0],
		a.values[1] - b.values[1],
		a.values[2] - b.values[2]);
}

inline Vector3 operator*(const Vector3& a, const Vector3& b) 
{
	return Vector3::Vector3(
		a.values[0] * b.values[0],
		a.values[1] * b.values[1],
		a.values[2] * b.values[2]);
}

inline Vector3 operator*(const double scalar, const Vector3& vec3) 
{
	return Vector3::Vector3(
		scalar * vec3.values[0],
		scalar * vec3.values[1],
		scalar * vec3.values[2]);
}

inline Vector3 operator*(const Vector3& vec3, const double scalar) { return scalar * vec3; }

inline Vector3 operator/(Vector3 vec3, const double scalar) { return (1 / scalar) * vec3; }

inline double dot(const Vector3& a, const Vector3& b) { return a.values[0] * b.values[0]+ a.values[1] * b.values[1] + a.values[2] * b.values[2]; }

inline Vector3 cross(const Vector3& a, const Vector3& b)
{
	return Vector3(
		a.values[1] * b.values[2] - a.values[2] * b.values[1],
		a.values[2] * b.values[0] - a.values[0] * b.values[2],
		a.values[0] * b.values[1] - a.values[1] * b.values[0]);
}

inline Vector3 Normalise(const Vector3 vec3) { return vec3 / vec3.length(); }

//inline Vec3 RandomUnitVector() { return Normalise(Sphere::RandomPointInUnitSphere());/*Normalise(Vec3::Random01());*/ }

// Type aliases
using Point3 = Vector3; // 3D Point
using Colour = Vector3; // RGB Colour
#endif