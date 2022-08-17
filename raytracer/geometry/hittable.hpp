#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"

struct HitRecord {
	Point3 Point;
	Vec3 Normal;
	double t;
	bool IsFrontFace;

	inline void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal) 
	{
		IsFrontFace = dot(ray.Direction, outwardNormal) < 0;
		Normal = IsFrontFace ? outwardNormal : -outwardNormal;
	}
};

class Hittable {
public:
	virtual bool IsHit(const Ray& ray, const double tMin, const double tMax, HitRecord& hitRecord) const = 0;
};

inline bool InBoundsInclusive(const double val, const double min, const double max) { return min <= val && val <= max; }

#endif
