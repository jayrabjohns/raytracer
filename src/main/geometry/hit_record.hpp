#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include <memory>

#include "vec3.hpp"
#include "ray.hpp"

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
#endif
