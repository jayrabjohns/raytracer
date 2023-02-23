#ifndef METAL_H
#define METAL_H

#include "material.hpp"

class Metal: public Material {
public:
  const Colour albedo;
  const double fuzziness;

public:
  Metal(Colour albedo);
  Metal(Colour albedo, double fuzzyness);
  virtual bool scatter(const Ray& ray, const HitRecord& hit_record, Colour& attenuation, Ray& scattered) const override;
};
#endif 
