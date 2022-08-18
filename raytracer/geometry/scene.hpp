#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>

#include "hittable.hpp"
#include "../camera.hpp"

class Scene
{
public:
	std::shared_ptr<Camera> camera;
	std::vector<std::shared_ptr<Hittable>> Objects;

public:
	Scene();
	Scene(const std::shared_ptr<Camera> camera);

	void Clear();
	void Add(const std::shared_ptr<Hittable> hittable);
	void Add(const std::shared_ptr<Camera> camera);

	virtual bool IsHit(const Ray& ray, const double tMin, const double tMax, HitRecord& hitRecord) const;
};

#endif