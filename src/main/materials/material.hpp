#ifndef MATERIAL_H
#define MATERIAL_H

#include "../geometry/ray.hpp"
#include "../geometry/hittable.hpp"
#include "../geometry/hit_record.hpp"

class Material {
public:
  virtual bool scatter(const Ray& ray, const HitRecord& hit_record, Colour& attenuation, Ray& scattered) const = 0;
};
#endif
