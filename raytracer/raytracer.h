#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "geometry/ray.h"
#include "geometry/scene.h"
class Raytracer
{
public:
	Colour GetRayColour(const Ray& ray, const Scene& scene);
	void Render(const int width, const int aspectRatio, const Scene& scene);
	std::string GetImagePPM(const int width, const int height);
};
#endif 
