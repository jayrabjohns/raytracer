#ifndef VEC3_H
#define VEC3_H

#include <cmath>
#include <iostream>

class vec3 
{
public:
	double vals[3];

public:
	vec3();
	vec3(const double x, const double y, const double z);

	double x() const;
	double y() const;
	double z() const;

	double length() const;
	double lengthSqr() const;

	double operator[](const int i) const;
	double& operator[](const int i);
	vec3 operator-() const;
	vec3& operator+=(const vec3& vec3);
	vec3& operator*=(const double t);
	vec3& operator/=(const double t);
};

inline std::ostream& operator<<(std::ostream& out, const vec3& vec3) { return out << vec3.vals[0] << ' ' << vec3.vals[1] << ' ' << vec3.vals[2]; }

inline vec3 operator+(const vec3& a, const vec3& b) 
{
	return vec3(
		a.vals[0] + b.vals[0],
		a.vals[1] + b.vals[1],
		a.vals[2] + b.vals[2]);
}

inline vec3 operator-(const vec3& a, const vec3& b) 
{
	return vec3(
		a.vals[0] - b.vals[0],
		a.vals[1] - b.vals[1],
		a.vals[2] - b.vals[2]);
}

inline vec3 operator*(const vec3& a, const vec3& b) 
{
	return vec3::vec3(
		a.vals[0] * b.vals[0],
		a.vals[1] * b.vals[1],
		a.vals[2] * b.vals[2]);
}

inline vec3 operator*(const double scalar, const vec3& vec3) 
{
	return vec3::vec3(
		scalar * vec3.vals[0],
		scalar * vec3.vals[1],
		scalar * vec3.vals[2]);
}

inline vec3 operator*(const vec3& vec3, const double scalar) { return scalar * vec3; }

inline vec3 operator/(vec3 vec3, const double scalar) { return (1 / scalar) * vec3; }

inline double dot(const vec3& a, const vec3& b) { return a.vals[0] * b.vals[0]+ a.vals[1] * b.vals[1] + a.vals[2] * b.vals[2]; }

inline vec3 cross(const vec3& a, const vec3& b)
{
	return vec3(
		a.vals[1] * b.vals[2] - a.vals[2] * b.vals[1],
		a.vals[2] * b.vals[0] - a.vals[0] * b.vals[2],
		a.vals[0] * b.vals[1] - a.vals[1] * b.vals[0]);
}

inline vec3 normalise(const vec3 vec3) { return vec3 / vec3.length(); }

// Type aliases
using point3 = vec3; // 3D Point
using colour = vec3; // RGB Colour
#endif