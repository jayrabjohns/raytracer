#ifndef PLANE_H
#define PLANE_H

#include "hittable.hpp"

class Plane: public Hittable {
public:
  Point3 a, b, c;

public:
  Plane(const Point3& a, const Point3& b, const Point3& c);

  virtual bool is_hit(const Ray& ray, const double t_min, const double t_max, HitRecord& hit_record) const override;
};

#endif
