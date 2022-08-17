#include "scene.hpp"

Scene::Scene() {}
Scene::Scene(const std::shared_ptr<Hittable> hittable) { Objects.push_back(hittable); }

void Scene::Clear() { Objects.clear(); }
void Scene::Add(const std::shared_ptr<Hittable> hittable) { Objects.push_back(hittable); }

bool Scene::IsHit(const Ray& ray, const double tMin, const double tMax, HitRecord& hitRecord) const
{
	HitRecord currentClosest;
	currentClosest.t = tMax;

	bool hit = false;
	for (const auto& object : Objects)
	{
		if (object->IsHit(ray, tMin, currentClosest.t, currentClosest))
		{
			hit = true;
			hitRecord = currentClosest;
		}
	}

	return hit;
}
