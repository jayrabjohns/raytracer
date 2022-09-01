#include "sphere.hpp"

Sphere::Sphere() : centre(Point3()), radius(0.0) {}
Sphere::Sphere(const Point3 centre, const double radius, std::shared_ptr<Material> material) : centre(centre), radius(radius), material(material) {}

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
	Vector3 oc = ray.origin - centre;
	double a = ray.direction.lengthSqr();
	double halfB = dot(oc, ray.direction);
	double c = oc.lengthSqr() - radius * radius;
	double discriminant = halfB * halfB - a * c;

	double root;
	if (discriminant >= 0.0 && TryGetClosestRoot(discriminant, halfB, a, tMin, tMax, root))
	{
		hitRecord.t = root;
		hitRecord.point = ray.at(root);
		Vector3 outwardNormal = (hitRecord.point - centre) / radius;
		hitRecord.SetFaceNormal(ray, outwardNormal);
		hitRecord.material = material;

		return true;
	}
	return false;
}
