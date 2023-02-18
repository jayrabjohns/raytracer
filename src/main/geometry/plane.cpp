#include "plane.hpp"

Plane::Plane(const Point3& a, const Point3& b, const Point3& c): a(a), b(b), c(c) {}

bool Plane::is_hit(const Ray& ray, const double t_min, const double t_max, HitRecord& hit_record) const {
  Vector3 plane_normal = -1.0 * cross(a - b, b - c);
  double ray_dot = dot(ray.direction, plane_normal);

  // Considered parallel if dot lies
  double tolerance = 0.05;
  if (!in_bounds_inclusive(ray_dot, t_min, t_max)) {
    // https://en.wikipedia.org/wiki/Line%E2%80%93plane_intersection#Algebraic_form
    hit_record.t = dot((a - ray.origin), plane_normal) / ray_dot;
    hit_record.point = ray.at(hit_record.t);
    hit_record.set_face_normal(ray, plane_normal);
    return true;
  }
  return false;
}
