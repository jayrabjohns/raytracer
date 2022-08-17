#include "plane.hpp"

Plane::Plane(const Point3& a, const Point3& b, const Point3& c) : A(a), B(b), C(c) {}

bool Plane::IsHit(const Ray& ray, const double tMin, const double tMax, HitRecord& hitRecord) const
{
	Vec3 planeNormal = -cross(A - B, B - C);
	double rayDot = dot(ray.Direction, planeNormal);

	// Considered parallel if dot lies
	double tolerance = 0.05;
	if (!InBoundsInclusive(rayDot, tMin, tMax))
	{
		// https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection#Algebraic_form
		hitRecord.t =  dot((A - ray.Origin), planeNormal) / rayDot;
		hitRecord.Point = ray.at(hitRecord.t);
		hitRecord.SetFaceNormal(ray, planeNormal);
		return true;
	}
	return false;
}
