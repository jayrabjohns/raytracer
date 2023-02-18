#include "metal.hpp"
#include "../utils/math_utils.hpp"
#include "../geometry/sphere.hpp"

Metal::Metal(const Colour& albedo): albedo(albedo), fuzziness(0.0) {}
Metal::Metal(const Colour& albedo, const double fuzziness): albedo(albedo), fuzziness(clamp_01(fuzziness)) {}

bool Metal::scatter(const Ray& ray, const HitRecord& hit_record, Colour& attenuation, Ray& scattered) const {
  Vector3 reflected = ray.direction.normalise().reflect(hit_record.normal);
  scattered = Ray(hit_record.point, reflected + fuzziness * Sphere::random_point_in_unit_sphere());
  attenuation = albedo;

  return (dot(scattered.direction, hit_record.normal) > 0.0);
}
