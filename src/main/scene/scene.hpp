#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>

#include "../geometry/hittable.hpp"
#include "camera.hpp"

class Scene {
public:
  std::shared_ptr<Camera> camera;
  std::vector<std::shared_ptr<Hittable>> objects;

public:
  Scene();
  Scene(std::shared_ptr<Camera> camera);

  void clear();
  void add(std::shared_ptr<Hittable> hittable);
  void add(std::shared_ptr<Camera> camera);

  virtual bool is_hit(const Ray& ray, double t_min, double t_max, HitRecord& hit_record) const;
};
#endif
