#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "../utils/math_utils.hpp"

class Vec3 
{
public:
	double values[3];

public:
	Vec3();
	Vec3(const double x, const double y, const double z);

	double x() const;
	double y() const;
	double z() const;

	double length() const;
	double lengthSqr() const;

	double operator[](const int i) const;
	double& operator[](const int i);
	Vec3 operator-() const;
	Vec3& operator+=(const Vec3& vec3);
	Vec3& operator*=(const double t);
	Vec3& operator/=(const double t);

	inline static Vec3 Random01() { return Vec3(RandomDouble01(), RandomDouble01(), RandomDouble01()); }

	inline static Vec3 Random(double min, double max) { return Vec3(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max)); }
};

inline std::ostream& operator<<(std::ostream& out, const Vec3& vec3) { return out << vec3.values[0] << ' ' << vec3.values[1] << ' ' << vec3.values[2]; }

inline Vec3 operator+(const Vec3& a, const Vec3& b) 
{
	return Vec3(
		a.values[0] + b.values[0],
		a.values[1] + b.values[1],
		a.values[2] + b.values[2]);
}

inline Vec3 operator-(const Vec3& a, const Vec3& b) 
{
	return Vec3(
		a.values[0] - b.values[0],
		a.values[1] - b.values[1],
		a.values[2] - b.values[2]);
}

inline Vec3 operator*(const Vec3& a, const Vec3& b) 
{
	return Vec3::Vec3(
		a.values[0] * b.values[0],
		a.values[1] * b.values[1],
		a.values[2] * b.values[2]);
}

inline Vec3 operator*(const double scalar, const Vec3& vec3) 
{
	return Vec3::Vec3(
		scalar * vec3.values[0],
		scalar * vec3.values[1],
		scalar * vec3.values[2]);
}

inline Vec3 operator*(const Vec3& vec3, const double scalar) { return scalar * vec3; }

inline Vec3 operator/(Vec3 vec3, const double scalar) { return (1 / scalar) * vec3; }

inline double dot(const Vec3& a, const Vec3& b) { return a.values[0] * b.values[0]+ a.values[1] * b.values[1] + a.values[2] * b.values[2]; }

inline Vec3 cross(const Vec3& a, const Vec3& b)
{
	return Vec3(
		a.values[1] * b.values[2] - a.values[2] * b.values[1],
		a.values[2] * b.values[0] - a.values[0] * b.values[2],
		a.values[0] * b.values[1] - a.values[1] * b.values[0]);
}

inline Vec3 Normalise(const Vec3 vec3) { return vec3 / vec3.length(); }

//inline Vec3 RandomUnitVector() { return Normalise(Sphere::RandomPointInUnitSphere());/*Normalise(Vec3::Random01());*/ }

// Type aliases
using Point3 = Vec3; // 3D Point
using Colour = Vec3; // RGB Colour
#endif