#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <mutex>

#include "geometry/ray.hpp"
#include "geometry/scene.hpp"
#include "camera.hpp"

struct imageOptions
{
	int width;
	int samplesPerPixel;
	int maxRayBounces;
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
	static Colour GetRayColour(const Ray& ray, const Scene& scene, const int maxDepth);
	static void RenderChunk(renderOptions renderOps);
	double Render(const imageOptions& imgOps, const Scene& scene, const char* filePath)
	{
#ifdef RAYTRACER_USE_SINGLE_THREAD
		return RenderSync(imgOps, scene, filePath);
#else
		return RenderAsync(imgOps, scene, filePath);
#endif
	}

private:
	double RenderSync(const imageOptions& imageOps, const Scene& scene, const char* filePath);
	double RenderAsync(const imageOptions& imageOps, const Scene& scene, const char* filePath);
};
#endif 
