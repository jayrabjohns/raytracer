#include <iostream>
#include <string>

#include "geometry/plane.h"
#include "geometry/scene.h"
#include "geometry/sphere.h"
#include "raytracer.h"
#include "utils/math_utils.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "image_creation/stb_image_write.h"

double HitSphere(const Point3& centre, const double radius, const Ray& ray)
{
	// Chapter 5.1
	Vec3 oc = ray.Origin - centre;
	double a = ray.Direction.lengthSqr();
	double bHalf = dot(oc, ray.Direction);
	double c = oc.lengthSqr() - radius * radius;
	double discriminant = bHalf * bHalf - a * c;

	// Chapter 6
	return (discriminant < 0.0 ? -1.0 : (-bHalf - std::sqrt(discriminant)) / a);
}

Colour Raytracer::GetRayColour(const Ray& ray, const Scene& scene)
{
	HitRecord hitRecord;
	if (scene.IsHit(ray, 0.0, infinity, hitRecord))
	{
		return 0.5 * (hitRecord.Normal + Colour(1.0, 1.0, 1.0));
	}

	Vec3 dir = Normalise(ray.Direction);
	double t = 0.5 * (dir.y() + 1.0);
	return (1.0 - t) * Colour(1.0, 1.0, 1.0) + t * Colour(0.5, 0.7, 1.0);
}

void Raytracer::CircleDemo()
{
	// Image
	int width = 800;
	double aspectRatio = 16.0 / 9.0;

	// World
	Scene scene;
	//scene.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100));
	scene.Add(std::make_shared<Plane>(Point3(1.0, -5.0, 0.0), Point3(0.0, -5.0, 0.0), Point3(0.0, -5.0, -1.0), 0.0));
	scene.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5));

	Render(width, aspectRatio, scene);
}

void Raytracer::Render(const int width, const int aspectRatio, const Scene& scene)
{
	int height = static_cast<int>(width / aspectRatio);

	// Camera
	double viewPortHeight = 2.0;
	double viewPortWidth = aspectRatio * viewPortHeight;
	double focalLength = 1.0;

	// Scene
	Point3 origin = Point3();
	Vec3 horizontal = Vec3(viewPortWidth, 0.0, 0.0);
	Vec3 vertical = Vec3(0.0, viewPortHeight, 0.0);
	Vec3 lowerLeft = origin - (horizontal / 2.0) - (vertical / 2.0) - Vec3(0.0, 0.0, focalLength);

	// Render
	int numChannels = 3;
	uint8_t* data = new uint8_t[width * height * numChannels];
	int index = 0;

	for (int i = height - 1; i >= 0; --i)
	{
		//std::cerr << "\rScanlines remaining: " << (height - i) << ' ' << std::flush;
		for (int j = 0; j < width; ++j)
		{
			double u = double(j) / (width - 1);
			double v = double(i) / (height - 1);

			Ray ray = Ray(origin, lowerLeft + u * horizontal + v * vertical - origin);
			Colour pixleColour = GetRayColour(ray, scene) * 255.0;
			data[index++] = static_cast<uint8_t>(pixleColour.x());
			data[index++] = static_cast<uint8_t>(pixleColour.y());
			data[index++] = static_cast<uint8_t>(pixleColour.z());
		}
	}

	stbi_write_png("..\\..\\..\\..\\out.png", width, height, numChannels, data, width * numChannels);
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
			double r = double(i) / (width - 1);
			double g = double(j) / (height - 1);
			double b = 0.25;

			int rInt = static_cast<int>(255.999 * r);
			int gInt = static_cast<int>(255.999 * g);
			int bInt = static_cast<int>(255.999 * b);

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
