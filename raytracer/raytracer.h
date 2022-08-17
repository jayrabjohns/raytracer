#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "geometry/ray.h"
#include "geometry/scene.h"
class Raytracer
{
public:
	Colour GetRayColour(const Ray& ray, const Scene& scene);
	void Render(const int width, const int aspectRatio, const Scene& scene);
	void CircleDemo();
	void GenerateAndWriteJPGDemo(const int width, const int height, const int numChannels, const int quality = 100);
	std::string GetImagePPM(const int width, const int height);
};
#endif 
