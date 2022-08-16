#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct HitRecord {
	Point3 Point;
	Vec3 Normal;
	double t;
};

class Hittable {
public:
	virtual bool IsHit(const Ray& ray, const double tMin, const double tMax, HitRecord& hitRecord) const = 0;
};

#endif
