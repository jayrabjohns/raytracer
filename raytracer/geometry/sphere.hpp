#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"
#include "vec3.hpp"

class Sphere : public Hittable
{
public:
	Point3 Centre;
	double Radius;

public:
	Sphere();
	Sphere(const Point3 centre, const double radius);

	virtual bool IsHit(const Ray& ray, const double tMin, const double tMax, HitRecord& hitRecord) const override;
};

#endif
