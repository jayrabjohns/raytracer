#include <iostream>
#include <string>

#include "raytracer.hpp"
#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"
#include "utils/math_utils.hpp"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"

Colour Raytracer::GetRayColour(const Ray& ray, const Scene& scene, const int depth)
{
	if (depth <= 0) { return Colour(0.0, 0.0, 0.0); }

	HitRecord hitRecord;
	if (scene.IsHit(ray, 0.001, infinity, hitRecord))
	{
		Point3 target = hitRecord.Point + hitRecord.Normal + Sphere::RandomPointInHemiSphere(hitRecord.Normal);
		return 0.5 * GetRayColour(Ray(hitRecord.Point, target - hitRecord.Point), scene, depth - 1);
	}

	Vec3 dir = Normalise(ray.Direction);
	double t = 0.5 * (dir.y() + 1.0);
	return (1.0 - t) * Colour(1.0, 1.0, 1.0) + t * Colour(0.5, 0.7, 1.0);
}

void Raytracer::Render(const int width, const double aspectRatio, const double samplesPerPixel, const int maxRayBounces, const Scene& scene)
{
	int height = static_cast<int>(width / aspectRatio);
	int numChannels = 3;
	uint8_t* data = new uint8_t[width * height * numChannels];
	int index = 0;

	for (int i = height - 1; i >= 0; --i)
	{
		std::cout << "\rScanlines remaining: " << (i) << ' ' << std::flush;
		for (int j = 0; j < width; ++j)
		{
			Colour pixelColour;
			for (size_t s = 0; s < samplesPerPixel; ++s)
			{
				double u = (j + RandomDouble01()) / (width - 1);
				double v = (i + RandomDouble01()) / (height - 1);

				Ray ray = scene.camera.get()->RayAt(u, v);
				pixelColour += GetRayColour(ray, scene, maxRayBounces);
			}

			pixelColour /= samplesPerPixel;

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
	}

	stbi_write_png("..\\..\\..\\..\\img\\out.png", width, height, numChannels, data, width * numChannels);
	delete[] data;
}

std::string Raytracer::GetImagePPM(const int width, const int height)
{
	std::string out = "";

	out += "P3\n";
	out += std::to_string(width) + ' ' + std::to_string(height) + '\n';
	out += "255\n";

	for (size_t i = 0; i < height; i++)
	{
		std::cout << "\rScanlines remaining: " << i << ' ' << std::flush;
		for (size_t j = 0; j < width; j++)
		{
			double r = double(i) / (width - 1);
			double g = double(j) / (height - 1);
			double b = 0.25;

			int rInt = static_cast<int>(255.999 * r);
			int gInt = static_cast<int>(255.999 * g);
			int bInt = static_cast<int>(255.999 * b);

			out += rInt + ' ' + gInt + ' ' + bInt + ' ';
		}
		out += '\n';
	}
	return out;
}
