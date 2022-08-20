#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

class Ray
{
public:
	Point3 origin;
	Vec3 direction;

public:
	Ray();
	Ray(const Point3& origin, const Vec3& direction);

	Point3 at(const double t) const;
};
#endif