#ifndef SCENE_H
#define SCENE_H

#include "hittable.h"

#include <vector>
#include <memory>

class Scene
{
public:
	std::vector<std::shared_ptr<Hittable>> Objects;

public:
	Scene();
	Scene(const std::shared_ptr<Hittable> hittable);

	void Clear();
	void Add(const std::shared_ptr<Hittable> hittable);

	virtual bool IsHit(const Ray& ray, const double tMin, const double tMax, HitRecord& hitRecord) const;
};

#endif