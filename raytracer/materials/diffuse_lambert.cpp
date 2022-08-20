#include "diffuse_lambert.hpp"
#include "../geometry/sphere.hpp"

DiffuseLambert::DiffuseLambert(const Colour& albedo) :albedo(albedo) {}

bool DiffuseLambert::Scatter(const Ray& ray, const HitRecord& hitRecord, Colour& attenuation, Ray& scattered) const
{
	Vec3 scatterDir = hitRecord.normal + Sphere::RandomPointInHemiSphere(hitRecord.normal);

	if (scatterDir.isNearZero())
		scatterDir = hitRecord.normal;

	scattered = Ray(hitRecord.point, scatterDir);
	attenuation = albedo;

	return true;
}
