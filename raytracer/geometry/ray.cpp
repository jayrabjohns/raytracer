#include "ray.h"

Ray::Ray() {}

Ray::Ray(const Point3& origin, const Vec3& direction) : Origin(origin), Direction(direction) {}

Point3 Ray::at(const double t) const { return Origin + t * Direction; }
