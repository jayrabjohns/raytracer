#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "geometry/ray.hpp"
#include "geometry/scene.hpp"
#include "camera.hpp"

class Raytracer
{
public:
	Colour GetRayColour(const Ray& ray, const Scene& scene);
	void Render(const int width, const double aspectRatio, const double samplesPerPixel, const Scene& scene);
	std::string GetImagePPM(const int width, const int height);
};
#endif 
