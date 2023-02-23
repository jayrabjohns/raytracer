#include "dielectric.hpp"

Dielectric::Dielectric(const double refractive_index):
  refractive_index(refractive_index) {
}

double reflectance(const double cosine, const double refractive_index) {
  // https://en.wikipedia.org/wiki/Schlick%27s_approximation
  double r0 = (1.0 - refractive_index) / (1.0 + refractive_index);
  r0 = r0 * r0;
  return r0 + (1.0 - r0) * pow((1.0 - cosine), 5);
}

bool Dielectric::scatter(const Ray& ray, const HitRecord& hit_record, Colour& attenuation, Ray& scattered) const {
  attenuation = Colour(1.0, 1.0, 1.0);
  double refractive_ratio = hit_record.is_front_face ? (1.0 / refractive_index) : refractive_index;

  Vector3 ray_dir_normalised = -ray.direction.normalise();
  double cos_theta = fmin(dot(ray_dir_normalised, hit_record.normal), 1.0);
  double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

  bool can_refract = refractive_ratio * sin_theta <= 1.0; // Accounting for total internal reflection
  Vector3 direction = (can_refract && reflectance(cos_theta, refractive_ratio) <= random_double_01())
    ? ray_dir_normalised.refract(hit_record.normal, refractive_ratio)
    : ray_dir_normalised.reflect(hit_record.normal);

  scattered = Ray(hit_record.point, direction);
  return true;
}
