#ifndef HITTABLE_H
#define HITTABLE_H

#include <memory>

#include "ray.hpp"
#include "hit_record.hpp"
#include "../materials/material.hpp"

class Hittable {
public:
  virtual bool is_hit(const Ray& ray, double t_min, double t_max, HitRecord& hit_record) const = 0;
};
#endif
