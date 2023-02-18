#include "scene.hpp"

Scene::Scene() {}
Scene::Scene(const std::shared_ptr<Camera> camera): camera(camera) {}

void Scene::clear() {
  camera.reset();
  objects.clear();
}
void Scene::add(const std::shared_ptr<Hittable> hittable) { objects.push_back(hittable); }
void Scene::add(const std::shared_ptr<Camera> camera) { this->camera = camera; }

bool Scene::is_hit(const Ray& ray, const double t_min, const double t_max, HitRecord& hit_record) const {
  HitRecord current_closest;
  current_closest.t = t_max;

  bool hit = false;
  for (const auto& object : objects) {
    if (object->is_hit(ray, t_min, current_closest.t, current_closest)) {
      hit = true;
      hit_record = current_closest;
    }
  }

  return hit;
}
