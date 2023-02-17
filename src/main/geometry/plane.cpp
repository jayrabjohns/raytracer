#include "plane.hpp"

Plane::Plane(const Point3& a, const Point3& b, const Point3& c) : a(a), b(b), c(c) {}

bool Plane::IsHit(const Ray& ray, const double tMin, const double tMax, HitRecord& hitRecord) const
{
	Vector3 planeNormal = -cross(a - b, b - c);
	double rayDot = dot(ray.direction, planeNormal);

	// Considered parallel if dot lies
	double tolerance = 0.05;
	if (!InBoundsInclusive(rayDot, tMin, tMax))
	{
		// https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection#Algebraic_form
		hitRecord.t =  dot((a - ray.origin), planeNormal) / rayDot;
		hitRecord.point = ray.at(hitRecord.t);
		hitRecord.SetFaceNormal(ray, planeNormal);
		return true;
	}
	return false;
}
