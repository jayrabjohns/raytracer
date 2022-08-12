#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class Ray
{
public:
	Point3 Origin;
	Vec3 Direction;

public:
	Ray();
	Ray(const Point3& origin, const Vec3& direction);

	Point3 at(const double t) const;
};
#endif