#ifndef HITTABLE_H
#define HITTABLE_H

#include <memory>

#include "ray.hpp"
#include "../materials/material.hpp"

class Material;

struct HitRecord {
  Point3 point;
  Vector3 normal;
  std::shared_ptr<Material> material;
  double t;
  bool is_front_face;

  inline void set_face_normal(const Ray& ray, const Vector3& outward_normal) {
    is_front_face = dot(ray.direction, outward_normal) < 0;
    normal = is_front_face ? outward_normal : -outward_normal;
  }
};

class Hittable {
public:
  virtual bool is_hit(const Ray& ray, const double tMin, const double tMax, HitRecord& hitRecord) const = 0;
};

inline bool in_bounds_inclusive(const double val, const double min, const double max) { return min <= val && val <= max; }

#endif
