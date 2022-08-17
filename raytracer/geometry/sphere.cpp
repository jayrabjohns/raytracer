#include "sphere.hpp"

Sphere::Sphere() : Centre(Point3()), Radius(0.0) {}
Sphere::Sphere(const Point3 centre, const double radius) : Centre(centre), Radius(radius) {}

inline bool TryGetClosestRoot(const double discriminant, const double halfB, const double a, const double tMin, const double tMax, double& root)
{
	double discriminantSqrt = std::sqrt(discriminant);
	root = (-halfB - discriminantSqrt) / a;

	if (!InBoundsInclusive(root, tMin, tMax))
	{
		root = (-halfB + discriminantSqrt) / a;
		if (!InBoundsInclusive(root, tMin, tMax))
		{
			root = 0.0;
			return false;
		}
	}
	return true;
}

bool Sphere::IsHit(const Ray& ray, const double tMin, const double tMax, HitRecord& hitRecord) const
{
	Vec3 oc = ray.Origin - Centre;
	double a = ray.Direction.lengthSqr();
	double halfB = dot(oc, ray.Direction);
	double c = oc.lengthSqr() - Radius * Radius;
	double discriminant = halfB * halfB - a * c;

	double root;
	if (discriminant >= 0 && TryGetClosestRoot(discriminant, halfB, a, tMin, tMax, root))
	{
		hitRecord.t = root;
		hitRecord.Point = ray.at(root);
		Vec3 outwardNormal = (hitRecord.Point - Centre) / Radius;
		hitRecord.SetFaceNormal(ray, outwardNormal);

		return true;
	}
	return false;
}
