#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "ray.h"
class Raytracer
{
public:
	Colour GetRayColour(const Ray& ray);
	void RenderDemo(const int width, const int height, const int quality);
	void GenerateAndWriteJPGDemo(const int width, const int height, const int numChannels, const int quality = 100);
	std::string GetImagePPM(const int width, const int height);
};
#endif 
