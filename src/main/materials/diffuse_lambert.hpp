#ifndef DIFFUSE_LAMBERT_H
#define DIFFUSE_LAMBERT_H

#include "material.hpp"
#include "../geometry/vec3.hpp"

class DiffuseLambert: public Material {
public:
  const Colour albedo;

public:
  DiffuseLambert(Colour albedo);

  virtual bool scatter(const Ray& ray, const HitRecord& hit_record, Colour& attenuation, Ray& scattered) const override;
};
#endif
