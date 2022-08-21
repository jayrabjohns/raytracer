#ifndef METAL_H
#define METAL_H

#include "material.hpp"

class Metal : public Material
{
public:
	Colour albedo;
	double fuzziness;

public:
	Metal(const Colour& albedo);
	Metal(const Colour& albedo, const double fuzzyness);
	virtual bool Scatter(const Ray& ray, const HitRecord& hitRecord, Colour& attenuation, Ray& scattered) const override;
};

#endif 
