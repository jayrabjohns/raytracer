#include "metal.hpp"

Metal::Metal(const Colour& albedo) : albedo(albedo) {}

bool Metal::Scatter(const Ray& ray, const HitRecord& hitRecord, Colour& attenuation, Ray& scattered) const
{
	Vec3 reflected = ray.direction.Normalised().reflect(hitRecord.normal);
	scattered = Ray(hitRecord.point, reflected);
	attenuation = albedo;

	return (dot(scattered.direction, hitRecord.normal) > 0.0);
}
