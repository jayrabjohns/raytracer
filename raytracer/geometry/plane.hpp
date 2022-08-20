#ifndef PLANE_H
#define PLANE_H

#include "hittable.hpp"

class Plane : public Hittable
{
public:
	Point3 a, b, c;

public:
	Plane(const Point3& a, const Point3& b, const Point3& c);

	virtual bool IsHit(const Ray& ray, const double tMin, const double tMax, HitRecord& hitRecord) const override;
};

#endif