#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

#include "../utils/math_utils.hpp"

class Vec3 
{
public:
	double Vals[3];

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

inline std::ostream& operator<<(std::ostream& out, const Vec3& vec3) { return out << vec3.Vals[0] << ' ' << vec3.Vals[1] << ' ' << vec3.Vals[2]; }

inline Vec3 operator+(const Vec3& a, const Vec3& b) 
{
	return Vec3(
		a.Vals[0] + b.Vals[0],
		a.Vals[1] + b.Vals[1],
		a.Vals[2] + b.Vals[2]);
}

inline Vec3 operator-(const Vec3& a, const Vec3& b) 
{
	return Vec3(
		a.Vals[0] - b.Vals[0],
		a.Vals[1] - b.Vals[1],
		a.Vals[2] - b.Vals[2]);
}

inline Vec3 operator*(const Vec3& a, const Vec3& b) 
{
	return Vec3::Vec3(
		a.Vals[0] * b.Vals[0],
		a.Vals[1] * b.Vals[1],
		a.Vals[2] * b.Vals[2]);
}

inline Vec3 operator*(const double scalar, const Vec3& vec3) 
{
	return Vec3::Vec3(
		scalar * vec3.Vals[0],
		scalar * vec3.Vals[1],
		scalar * vec3.Vals[2]);
}

inline Vec3 operator*(const Vec3& vec3, const double scalar) { return scalar * vec3; }

inline Vec3 operator/(Vec3 vec3, const double scalar) { return (1 / scalar) * vec3; }

inline double dot(const Vec3& a, const Vec3& b) { return a.Vals[0] * b.Vals[0]+ a.Vals[1] * b.Vals[1] + a.Vals[2] * b.Vals[2]; }

inline Vec3 cross(const Vec3& a, const Vec3& b)
{
	return Vec3(
		a.Vals[1] * b.Vals[2] - a.Vals[2] * b.Vals[1],
		a.Vals[2] * b.Vals[0] - a.Vals[0] * b.Vals[2],
		a.Vals[0] * b.Vals[1] - a.Vals[1] * b.Vals[0]);
}

inline Vec3 Normalise(const Vec3 vec3) { return vec3 / vec3.length(); }

//inline Vec3 RandomUnitVector() { return Normalise(Sphere::RandomPointInUnitSphere());/*Normalise(Vec3::Random01());*/ }

// Type aliases
using Point3 = Vec3; // 3D Point
using Colour = Vec3; // RGB Colour
#endif