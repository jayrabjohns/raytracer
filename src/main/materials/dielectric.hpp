#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.hpp"

class Dielectric: public Material {
public:
  const double refractive_index;

public:
  Dielectric(double refractive_index);

  virtual bool scatter(const Ray& ray, const HitRecord& hitRecord, Colour& attenuation, Ray& scattered) const override;
};
#endif
