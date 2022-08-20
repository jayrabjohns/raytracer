#include "ray.hpp"

Ray::Ray() {}

Ray::Ray(const Point3& origin, const Vec3& direction) : origin(origin), direction(direction) {}

Point3 Ray::at(const double t) const { return origin + t * direction; }
