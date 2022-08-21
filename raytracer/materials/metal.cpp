#include "metal.hpp"
#include "../utils/math_utils.hpp"
#include "../geometry/sphere.hpp"

Metal::Metal(const Colour& albedo) : albedo(albedo), fuzziness(0.0) {}
Metal::Metal(const Colour& albedo, const double fuzziness) : albedo(albedo), fuzziness(Clamp01(fuzziness)) {}

bool Metal::Scatter(const Ray& ray, const HitRecord& hitRecord, Colour& attenuation, Ray& scattered) const
{
	Vec3 reflected = ray.direction.Normalised().reflect(hitRecord.normal);
	scattered = Ray(hitRecord.point, reflected + fuzziness * Sphere::RandomPointInUnitSphere());
	attenuation = albedo;

	return (dot(scattered.direction, hitRecord.normal) > 0.0);
}
