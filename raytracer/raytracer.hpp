#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <mutex>

#include "geometry/ray.hpp"
#include "geometry/scene.hpp"
#include "camera.hpp"

struct imageOptions
{
	const int width;
	const int samplesPerPixel;
	const int maxRayBounces;
	const int colourChannels;

	imageOptions(const int width, const int samplesPerPixel, const int maxRayBounces, const int colourChannels) : width(width), samplesPerPixel(samplesPerPixel), maxRayBounces(maxRayBounces), colourChannels(colourChannels) {}
};

struct renderOptions
{
	const imageOptions& imgOps;
	const int height;
	const Scene& scene;
	int startRow;
	int endRow;
	uint8_t* data;
	std::mutex& dataMutex;

	renderOptions(const imageOptions& imgOps, int height, const Scene& scene, int startRow, int endRow, uint8_t* data, std::mutex& dataMutex) : imgOps(imgOps), height(height), scene(scene), startRow(startRow), endRow(endRow), data(data), dataMutex(dataMutex) {}
};

class Raytracer
{
public:
	double Render(renderOptions& renderOps, uint8_t* data, const bool useSingleThread = false);
	double RenderPng(const imageOptions& imgOps, const Scene& scene, const char* filePath, const bool useSingleThread = false);

private:
	static Colour GetRayColour(const Ray& ray, const Scene& scene, const int maxDepth);
	static void RenderChunk(renderOptions renderOps);
};
#endif 
