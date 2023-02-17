#include "dielectric.hpp"

Dielectric::Dielectric(const double refractiveIndex) : refractiveIndex(refractiveIndex) {}

double Reflectance(double cosine, double refractiveIndex)
{
	// https://en.wikipedia.org/wiki/Schlick%27s_approximation
	double r0 = (1.0 - refractiveIndex) / (1.0 + refractiveIndex);
	r0 = r0 * r0;
	return r0 + (1.0 - r0) * pow((1.0 - cosine), 5);
}

bool Dielectric::Scatter(const Ray& ray, const HitRecord& hitRecord, Colour& attenuation, Ray& scattered) const
{
	attenuation = Colour(1.0, 1.0, 1.0);
	double refractiveRatio = hitRecord.isFrontFace ? (1.0 / refractiveIndex) : refractiveIndex;	

	Vector3 rayDirNormalised = -ray.direction.Normalised();
	double cosTheta = fmin(dot(rayDirNormalised, hitRecord.normal), 1.0);
	double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

	bool canRefract = refractiveRatio * sinTheta <= 1.0; // Accounting for total internal reflection
	Vector3 direction = (canRefract && Reflectance(cosTheta, refractiveRatio) <= RandomDouble01())
		? rayDirNormalised.refract(hitRecord.normal, refractiveRatio)
		: rayDirNormalised.reflect(hitRecord.normal);

	scattered = Ray(hitRecord.point, direction);
	return true;
}
