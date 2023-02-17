#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.hpp"

class Dielectric : public Material
{
public:
	double refractiveIndex;

public:
	Dielectric(const double refractiveIndex);

	virtual bool Scatter(const Ray& ray, const HitRecord& hitRecord, Colour& attenuation, Ray& scattered) const override;
};

#endif
