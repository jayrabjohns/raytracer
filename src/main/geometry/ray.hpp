#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

class Ray
{
public:
	Point3 origin;
	Vector3 direction;

public:
	Ray();
	Ray(const Point3& origin, const Vector3& direction);

	Point3 at(const double t) const;
};
#endif