#include <memory>

#include "sphere.hpp"

Sphere::Sphere():
  centre(Point3()),
  radius(0.0) {
}

Sphere::Sphere(const Point3 centre, const double radius, const std::shared_ptr<Material> material):
  centre(centre),
  radius(radius),
  material(material) {
}

bool tryGetClosestRoot(const double discriminant, const double half_b, const double a, const double t_min, const double t_max, double& root) {
  double discriminant_sqrt = std::sqrt(discriminant);
  root = (-half_b - discriminant_sqrt) / a;

  if (!in_bounds_inclusive(root, t_min, t_max)) {
    root = (-half_b + discriminant_sqrt) / a;
    if (!in_bounds_inclusive(root, t_min, t_max)) {
      root = 0.0;
      return false;
    }
  }
  return true;
}

bool Sphere::is_hit(const Ray& ray, const double t_min, const double t_max, HitRecord& hit_record) const {
  Vector3 oc = ray.origin - centre;
  double a = ray.direction.length_sqr();
  double half_b = dot(oc, ray.direction);
  double c = oc.length_sqr() - radius * radius;
  double discriminant = half_b * half_b - a * c;

  double root;
  if (discriminant >= 0.0 && tryGetClosestRoot(discriminant, half_b, a, t_min, t_max, root)) {
    hit_record.t = root;
    hit_record.point = ray.at(root);
    Vector3 outward_normal = (hit_record.point - centre) / radius;
    hit_record.set_face_normal(ray, outward_normal);
    hit_record.material = material;

    return true;
  }
  return false;
}
