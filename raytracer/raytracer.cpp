#include <iostream>
#include <string>

#include "raytracer.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

bool HitSphere(const Point3& centre, double radius, const Ray& ray)
{
	// Chapter 5.1
	Vec3 oc = ray.Origin - centre;
	double a = dot(ray.Direction, ray.Direction);
	double b = 2.0 * dot(oc, ray.Direction);
	double c = dot(oc, oc) - radius * radius;
	double discriminant = b * b - 4.0 * a * c;
	return (discriminant > 0.0);
}

Colour Raytracer::GetRayColour(const Ray& ray)
{
	if (HitSphere(Point3(0.0, 0.0, -1.0), 0.5, ray))
	{
		return Colour(1.0, 0.0, 0.0);
	}

	Vec3 dir = Normalise(ray.Direction);
	double t = 0.5 * (dir.y() + 1.0);
	return (1.0 - t) * Colour(1.0, 1.0, 1.0) + t * Colour(0.5, 0.7, 1.0);
}

void Raytracer::RenderDemo(const int width, const int aspectRatio, const int quality)
{
	const int height = static_cast<int>(width / aspectRatio);

	// Camera
	const double viewPortHeight = 2.0;
	const double viewPortWidth = aspectRatio * viewPortHeight;
	const double focalLength = 1.0;

	// Scene
	const Point3 origin = Point3();
	const Vec3 horizontal = Vec3(viewPortWidth, 0.0, 0.0);
	const Vec3 vertical = Vec3(0.0, viewPortHeight, 0.0);
	const Vec3 lowerLeft = origin - (horizontal / 2.0) - (vertical / 2.0) - Vec3(0.0, 0.0, focalLength);

	const int numChannels = 3;
	uint8_t* data = new uint8_t[width * height * numChannels];
	int index = 0;

	for (size_t i = 0; i < height; i++)
	{
		std::cerr << "\rScanlines remaining: " << (height - i) << ' ' << std::flush;
		for (size_t j = 0; j < width; j++)
		{
			const double u = double(i) / (width - 1);
			const double v = double(j) / (height - 1);

			Ray r = Ray(origin, lowerLeft + u * horizontal + v * vertical - origin);
			Colour pixleColour = GetRayColour(r) * 255;
			data[index++] = pixleColour.x();
			data[index++] = pixleColour.y();
			data[index++] = pixleColour.z();
		}
	}

	stbi_write_jpg("..\\..\\..\\..\\out.jpg", width, height, numChannels, data, quality);
	delete[] data;
}

void Raytracer::GenerateAndWriteJPGDemo(const int width, const int height, const int numChannels, const int quality)
{
	uint8_t* data = new uint8_t[width * height * numChannels];
	int index = 0;

	for (size_t i = 0; i < height; i++)
	{
		std::cerr << "\rScanlines remaining: " << i << ' ' << std::flush;
		for (size_t j = 0; j < width; j++)
		{
			const double r = double(i) / (width - 1);
			const double g = double(j) / (height - 1);
			const double b = 0.25;

			const int rInt = static_cast<int>(255.999 * r);
			const int gInt = static_cast<int>(255.999 * g);
			const int bInt = static_cast<int>(255.999 * b);

			data[index++] = rInt;
			data[index++] = gInt;
			data[index++] = bInt;
		}
	}

	stbi_write_jpg("jpgTest.jpg", width, height, numChannels, data, quality);
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
