#include "diffuse_lambert.hpp"
#include "../geometry/sphere.hpp"

DiffuseLambert::DiffuseLambert(const Colour& albedo): albedo(albedo) {}

bool DiffuseLambert::scatter(const Ray& ray, const HitRecord& hit_record, Colour& attenuation, Ray& scattered) const {
  Vector3 scatter_dir = hit_record.normal + Sphere::random_point_in_hemi_sphere(hit_record.normal);

  if (scatter_dir.is_near_zero())
    scatter_dir = hit_record.normal;

  scattered = Ray(hit_record.point, scatter_dir);
  attenuation = albedo;

  return true;
}
