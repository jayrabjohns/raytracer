#ifndef RAY_H
#define RAY_H

#include "vec3.hpp"

class Ray {
public:
  Point3 origin;
  Vector3 direction;

public:
  Ray();
  Ray(Point3 origin, Vector3 direction);

  Point3 at(double t) const;
};
#endif
