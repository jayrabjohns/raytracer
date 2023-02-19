#ifndef HITTABLE_H
#define HITTABLE_H

#include <memory>

#include "ray.hpp"
#include "hit_record.hpp"
#include "../materials/material.hpp"

class Hittable {
public:
  virtual bool is_hit(const Ray& ray, const double t_min, const double t_max, HitRecord& hit_record) const = 0;
};

inline bool in_bounds_inclusive(const double val, const double min, const double max) { return min <= val && val <= max; }

#endif
