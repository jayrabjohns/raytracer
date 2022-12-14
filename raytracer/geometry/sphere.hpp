#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.hpp"
#include "vec3.hpp"

class Sphere : public Hittable
{
public:
	Point3 centre;
	double radius;
	std::shared_ptr<Material> material;

public:
	Sphere();
	Sphere(const Point3 centre, const double radius, std::shared_ptr<Material> material);

	virtual bool IsHit(const Ray& ray, const double tMin, const double tMax, HitRecord& hitRecord) const override;

	static Vector3 RandomPointOnUnitSphere()
	{
		return Normalise(RandomPointInUnitSphere());
	}

	static Vector3 RandomPointInUnitSphere()
	{
		while (true)
		{
			auto p = Vector3::Random(-1.0, 1.0);
			if (p.lengthSqr() >= 1) continue;
			return p;
		}
	}

	static Vector3 RandomPointInHemiSphere(const Vector3& normal)
	{
		Vector3 pointInUnitSphere = RandomPointInUnitSphere();
		if (dot(pointInUnitSphere, normal) > 0.0) // In the same hemisphere as the normal
			return pointInUnitSphere;
		else
			return -pointInUnitSphere;
	}
};

#endif
