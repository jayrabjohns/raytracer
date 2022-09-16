#include <iostream>
#include <string>
#include <thread>

#include "raytracer.hpp"
#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"
#include "utils/math_utils.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

double Raytracer::RenderPng(const imageOptions& imgOps, const Scene& scene, const char* filePath, const bool useSingleThread)
{
	int height = static_cast<int>((imgOps.width / scene.camera.get()->aspectRatio));
	int colourChannels = 3;
	uint8_t* data = new uint8_t[imgOps.width * height * colourChannels];
	std::mutex dataMutex;
	renderOptions renderOps(imgOps, height, scene, 0, height, data, dataMutex);

	double elapsedSecs = Render(renderOps, data, useSingleThread);
	stbi_write_png(filePath, renderOps.imgOps.width, height, colourChannels, data, renderOps.imgOps.width * colourChannels);

	delete[] data;
	return elapsedSecs;
}

double Raytracer::Render(renderOptions& renderOps, uint8_t* data, const bool useSingleThread)
{
	unsigned int hardwareThreads = std::thread::hardware_concurrency();
	unsigned int threadsNum = (hardwareThreads == 0 || useSingleThread ? 1 : hardwareThreads);
	std::thread* threads = new std::thread[threadsNum];

	time_t start, end;
	time(&start);

	int chunkSize = renderOps.height / threadsNum;
	for (size_t i = 0; i < threadsNum; ++i)
	{
		renderOps.startRow = i * chunkSize;
		renderOps.endRow = (i == threadsNum - 1 ? renderOps.height : renderOps.startRow + chunkSize);
		threads[i] = std::thread(&Raytracer::RenderChunk, renderOps);
	}

	for (size_t i = 0; i < threadsNum; ++i)
	{
		threads[i].join();
	}
	time(&end);
	double elapsedSecs = static_cast<double>(end - start);

	delete[] threads;
	return elapsedSecs;
}

inline Colour GetBackgroundColour(const Ray& ray)
{
	Vector3 dir = Normalise(ray.direction);
	double t = 0.5 * (dir.y() + 1.0);
	return (1.0 - t) * Colour(1.0, 1.0, 1.0) + t * Colour(0.5, 0.7, 1.0);
}

Colour Raytracer::GetRayColour(const Ray& ray, const Scene& scene, const int maxDepth)
{
	Ray r = ray;
	Colour rayColour = GetBackgroundColour(r);

	bool hit = false;
	Ray scattered;
	Colour attenuation;
	HitRecord hitRecord;
	for (int depth = 0; depth < maxDepth; ++depth)
	{
		if (depth == maxDepth) { return Colour(0.0, 0.0, 0.0); }
		else if (scene.IsHit(r, 0.001, infinity, hitRecord))
		{
			hit = true;
			if (hitRecord.material->Scatter(r, hitRecord, attenuation, scattered))
			{
				r = scattered;
				rayColour *= attenuation;
			}
		}
		else break;
	}

	return rayColour;
}

void Raytracer::RenderChunk(renderOptions renderOps)
{
	uint8_t* chunkData = new uint8_t[(renderOps.endRow - renderOps.startRow) * renderOps.imgOps.width * renderOps.imgOps.colourChannels]; // Each thread uses its own buffer to avoid loads of locking / unlocking shenanigans
	int index = 0;

	for (int i = renderOps.startRow; i < renderOps.endRow; ++i)
	{
		for (int j = 0; j < renderOps.imgOps.width; ++j)
		{
			Colour pixelColour;
			for (size_t s = 0; s < renderOps.imgOps.samplesPerPixel; ++s)
			{
				double u = (j + RandomDouble01()) / (renderOps.imgOps.width - 1);
				double v = (i + RandomDouble01()) / (renderOps.height - 1);
				v = 1.0 - v; // Flipping image so +y is up

				Ray ray = renderOps.scene.camera.get()->RayAt(u, v);
				pixelColour += GetRayColour(ray, renderOps.scene, renderOps.imgOps.maxRayBounces);
			}

			pixelColour /= renderOps.imgOps.samplesPerPixel;

			// Gamma-correct for gamma = 2.0
			double r = std::sqrt(pixelColour.x());
			double g = std::sqrt(pixelColour.y());
			double b = std::sqrt(pixelColour.z());

			r = 256.0 * Clamp(r, 0.0, 0.999);
			g = 256.0 * Clamp(g, 0.0, 0.999);
			b = 256.0 * Clamp(b, 0.0, 0.999);

			chunkData[index++] = static_cast<uint8_t>(r);
			chunkData[index++] = static_cast<uint8_t>(g);
			chunkData[index++] = static_cast<uint8_t>(b);
		}
	}

	const int imgOffset = renderOps.startRow * renderOps.imgOps.width * renderOps.imgOps.colourChannels;

	renderOps.dataMutex.lock();
	for (int i = 0; i < index; ++i)
	{
		int _i = i + imgOffset;
		renderOps.data[_i] = chunkData[i];
	}
	renderOps.dataMutex.unlock();

	delete[] chunkData;
}