#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.hpp"
#include "../materials/material.hpp"

class Material;

struct HitRecord {
	Point3 point;
	Vec3 normal;
	std::shared_ptr<Material> material;
	double t;
	bool isFrontFace;

	inline void SetFaceNormal(const Ray& ray, const Vec3& outwardNormal) 
	{
		isFrontFace = dot(ray.direction, outwardNormal) < 0;
		normal = isFrontFace ? outwardNormal : -outwardNormal;
	}
};

class Hittable {
public:
	virtual bool IsHit(const Ray& ray, const double tMin, const double tMax, HitRecord& hitRecord) const = 0;
};

inline bool InBoundsInclusive(const double val, const double min, const double max) { return min <= val && val <= max; }

#endif
