#include <iostream>
#include <string>
#include <thread>

#include "raytracer.hpp"
#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"
#include "utils/math_utils.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

inline Colour GetBackgroundColour(const Ray& ray)
{
	Vector3 dir = Normalise(ray.direction);
	double t = 0.5 * (dir.y() + 1.0);
	return (1.0 - t) * Colour(1.0, 1.0, 1.0) + t * Colour(0.5, 0.7, 1.0);
}

Colour Raytracer::GetRayColour(const Ray& ray, const Scene& scene, const int depth)
{
#if false
	// Recursive
	if (depth <= 0) { return Colour(0.0, 0.0, 0.0); }

	HitRecord hitRecord;
	if (scene.IsHit(ray, 0.001, infinity, hitRecord))
	{
		Ray scattered;
		Colour attenuation;
		if (hitRecord.material->Scatter(ray, hitRecord, attenuation, scattered))
		{
			return attenuation * GetRayColour(scattered, scene, depth - 1);
		}
	}

	return GetBackgroundColour(ray)
#else
	// Iterative
	Ray r = ray;
	Colour rayColour = GetBackgroundColour(r);

	bool hit = false;
	Ray scattered;
	Colour attenuation;
	HitRecord hitRecord;
	for (int d = depth; d >= 0; --d)
	{
		if (d == 0) { return Colour(0.0, 0.0, 0.0); }
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
#endif
}

double Raytracer::RenderSync(const imageOptions& imageOptions, const Scene& scene, const char* filePath)
{
	int height = (int)(imageOptions.width / scene.camera.get()->aspectRatio);
	int numChannels = 3;
	uint8_t* data = new uint8_t[imageOptions.width * height * numChannels];
	int index = 0;

	double elapsedTime = 0.0;
	time_t start, end;
	time(&start);

	for (int i = height - 1; i >= 0; --i)
	{
#ifndef RAYTRACER_NO_PROGRESS_BAR
		std::cout << "\r[" << elapsedTime << "s] Scanlines remaining: " << (i) << ' ' << std::flush;
#endif // PROGRESS_BAR
		for (int j = 0; j < imageOptions.width; ++j)
		{
			Colour pixelColour;
			for (size_t s = 0; s < imageOptions.samplesPerPixel; ++s)
			{
				double u = (j + RandomDouble01()) / (imageOptions.width - 1);
				double v = (i + RandomDouble01()) / (height - 1);

				Ray ray = scene.camera.get()->RayAt(u, v);
				pixelColour += GetRayColour(ray, scene, imageOptions.maxRayBounces);
			}

			pixelColour /= imageOptions.samplesPerPixel;

			// Gamma-correct for gamma = 2.0
			double r = std::sqrt(pixelColour.x());
			double g = std::sqrt(pixelColour.y());
			double b = std::sqrt(pixelColour.z());

			r = 256.0 * Clamp(r, 0.0, 0.999);
			g = 256.0 * Clamp(g, 0.0, 0.999);
			b = 256.0 * Clamp(b, 0.0, 0.999);

			data[index++] = static_cast<uint8_t>(r);
			data[index++] = static_cast<uint8_t>(g);
			data[index++] = static_cast<uint8_t>(b);
		}
#ifndef RAYTRACER_NO_PROGRESS_BAR
		time(&end);
		elapsedTime = double(end - start);
#endif // PROGRESS_BAR
	}

	time(&end);
	elapsedTime = double(end - start);

	stbi_write_png(filePath, imageOptions.width, height, numChannels, data, imageOptions.width * numChannels);
	delete[] data;

	return elapsedTime;
}

void Raytracer::RenderChunk(renderOptions renderOps)
{
	const int numChannels = 3;
	uint8_t* chunkData = new uint8_t[(renderOps.endRow - renderOps.startRow) * renderOps.imgOps.width * numChannels];
	int index = 0;

	for (int i = renderOps.endRow - 1; i >= renderOps.startRow; --i)
	{
		for (int j = 0; j < renderOps.imgOps.width; ++j)
		{
			Colour pixelColour;
			for (size_t s = 0; s < renderOps.imgOps.samplesPerPixel; ++s)
			{
				double u = (j + RandomDouble01()) / (renderOps.imgOps.width - 1);
				double v = (i + RandomDouble01()) / (renderOps.height - 1);

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

	renderOps.dataMutex.lock();
	for (int i = (renderOps.startRow * renderOps.imgOps.width * numChannels), cI = 0; cI < index; ++i, ++cI)
	{
		renderOps.data[i] = chunkData[cI];
	}
	renderOps.dataMutex.unlock();

	delete[] chunkData;
}

double Raytracer::RenderAsync(const imageOptions& imgOps, const Scene& scene, const char* filePath)
{
	int height = 451;//(int)(imgOps.width / scene.camera.get()->aspectRatio);
	int numChannels = 3;
	uint8_t* data = new uint8_t[imgOps.width * height * numChannels];
	std::mutex dataMutex;

	unsigned int hardwareThreads = std::thread::hardware_concurrency();
	unsigned int threadsNum = 2;//(hardwareThreads != 0 ? hardwareThreads : 1);
	std::thread* threads = new std::thread[threadsNum];

	renderOptions renderOps(imgOps, height, scene, 0, height, data, dataMutex);

	double elapsedTime = 0.0;
	time_t start, end;
	time(&start);

	int chunkSize = height / threadsNum;
	int lastChunkSize = chunkSize + height % threadsNum;
	for (size_t i = 0; i < threadsNum - 1; ++i)
	{
		renderOps.startRow = i * chunkSize;
		renderOps.endRow = renderOps.startRow + chunkSize;
		threads[i] = std::thread(&Raytracer::RenderChunk, renderOps);
	}

	renderOps.startRow = height - lastChunkSize;
	renderOps.endRow = height;
	threads[threadsNum - 1] = std::thread(&Raytracer::RenderChunk, renderOps);

	for (size_t i = 0; i < threadsNum; ++i)
	{
		threads[i].join();
	}

	time(&end);
	elapsedTime = double(end - start);

	stbi_write_png(filePath, renderOps.imgOps.width, height, numChannels, data, renderOps.imgOps.width * numChannels);

	delete[] threads;
	delete[] data;

	return elapsedTime;
}
