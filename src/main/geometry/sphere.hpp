#ifndef SPHERE_H
#define SPHERE_H

#include <memory>

#include "hittable.hpp"
#include "vec3.hpp"

class Sphere: public Hittable {
public:
  const Point3 centre;
  const double radius;
  const std::shared_ptr<Material> material;

public:
  Sphere();
  Sphere(Point3 centre, double radius, std::shared_ptr<Material> material);

  virtual bool is_hit(const Ray& ray, double t_min, double t_max, HitRecord& hit_record) const override;

  static inline Vector3 random_point_on_unit_sphere() {
    return normalise(random_point_in_unit_sphere());
  }

  static Vector3 random_point_in_unit_sphere() {
    while (true) {
      const auto p = Vector3::random(-1.0, 1.0);
      if (p.length_sqr() >= 1) continue;
      return p;
    }
  }

  static Vector3 random_point_in_hemi_sphere(const Vector3& normal) {
    Vector3 point_in_unit_sphere = random_point_in_unit_sphere();
    if (dot(point_in_unit_sphere, normal) > 0.0) { // In the same hemisphere as the normal
      return point_in_unit_sphere;
    }
    else {
      return -1.0 * point_in_unit_sphere;
    }
  }
};
#endif
