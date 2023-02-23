#ifndef PLANE_H
#define PLANE_H

#include "hittable.hpp"

class Plane: public Hittable {
public:
  const Point3 a, b, c;

public:
  Plane(Point3 a, Point3 b, Point3 c);

  virtual bool is_hit(const Ray& ray, double t_min, double t_max, HitRecord& hit_record) const override;
};
#endif
