#include<iostream>

#include "main.hpp"
//#define RAYTRACER_USE_SINGLE_THREAD
#include "raytracer.hpp"
#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"

#include "materials/diffuse_lambert.hpp"
#include "materials/metal.hpp"
#include "materials/dielectric.hpp"

int main()
{
	imageOptions imageOps;
	imageOps.width = 800;
	imageOps.samplesPerPixel = 32;
	imageOps.maxRayBounces = 50;

	auto camera = std::make_shared<Camera>();
	Scene scene = Scene(camera);
	DemoScene(scene);

	Raytracer raytracer = Raytracer();
	double timeElapsed = raytracer.Render(imageOps, scene, "..\\..\\..\\..\\img\\out.png");

	std::cerr << "\nDone." << std::endl;
	std::cout << "Total time: " << timeElapsed << 's' << std::endl;
	return 0;
}

std::shared_ptr<Sphere> GenRandomSphere(double x, double y, double z, double xLeeway, double yLeeway, double zLeeway, double radius)
{
	Point3 centre(x + xLeeway * RandomDouble01(), y + yLeeway * RandomDouble01(), z + zLeeway * RandomDouble01());

	double chooseMat = RandomDouble01();
	if (chooseMat <= 0.80)
	{
		Colour albedo = Colour::Random01() * Colour::Random01();
		auto sphereMat = std::make_shared<DiffuseLambert>(albedo);
		return std::make_shared<Sphere>(centre, radius, sphereMat);
	}
	else if (chooseMat <= 0.95)
	{
		Colour albedo = Colour::Random(0.5, 1.0);
		double fuzz = RandomDouble(0.0, 0.5);
		auto sphereMat = std::make_shared<Metal>(albedo, fuzz);
		return std::make_shared<Sphere>(centre, radius, sphereMat);
	}
	else
	{
		auto sphereMat = std::make_shared<Dielectric>(RandomDouble(0.5, 1.5));
		return std::make_shared<Sphere>(centre, radius, sphereMat);
	}
}

void RandomScene(Scene& scene)
{
	// Camera
	Point3 lookFrom = Point3(13.0, 2.0, 3.0);
	Point3 lookAt = Point3(0.0, 0.0, 0.0);
	Point3 camUp = Point3(0.0, 1.0, 0.0);
	double vFov = 20.0;
	double aspectRatio = 3.0 / 2.0;
	double aperture = 0.1;
	double distToFocus = 10.0;

	scene.camera.get()->Init(lookFrom, lookAt, camUp, vFov, aspectRatio, aperture, distToFocus, 0.0, infinity);

	// Scene
	auto groundMat = std::make_shared<DiffuseLambert>(Colour(0.5, 0.5, 0.5));
	auto ground = std::make_shared<Sphere>(Point3(0.0, -1000.0, 0.0), 1000.0, groundMat);
	scene.Add(ground);

	for (int x = -11; x < 11; ++x)
	{
		for (int z = -11; z < 11; ++z)
		{
			auto randomSphere = GenRandomSphere(x, 0.2, z, 0.9, 0.0, 0.9, 0.2);
			if ((randomSphere.get()->centre - Point3(4.0, 0.2, 0.0)).length() > 0.9) 
			{
				scene.Add(randomSphere);
			}
		}
	}

	auto mat1 = std::make_shared<Dielectric>(1.5);
	auto sphere1 = std::make_shared<Sphere>(Point3(0.0, 1.0, 0.0), 1.0, mat1);
	scene.Add(sphere1);

	auto mat2 = std::make_shared<DiffuseLambert>(Colour(0.4, 0.2, 0.1));
	auto sphere2 = std::make_shared<Sphere>(Point3(-4.0, 1.0, 0.0), 1.0, mat2);
	scene.Add(sphere2);

	auto mat3 = std::make_shared<Metal>(Colour(0.7, 0.6, 0.5), 0.0);
	auto sphere3 = std::make_shared<Sphere>(Point3(4.0, 1.0, 0.0), 1.0, mat3);
	scene.Add(sphere3);
}

void DemoScene(Scene& scene)
{
	auto groundMat = std::make_shared<DiffuseLambert>(Colour(0.8, 0.8, 0.0));
	//auto backMat = std::make_shared<DiffuseLambert>(Colour(0.7, 0.3, 0.3));
	auto centreMat = std::make_shared<Dielectric>(1.5);
	auto leftMat = std::make_shared<Metal>(Colour(0.8, 0.8, 0.8), 0.8);
	auto rightMat = std::make_shared<Metal>(Colour(0.8, 0.6, 0.2));

	scene.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, groundMat));
	//scene.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, backMat));
	scene.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, centreMat));
	scene.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), -0.4, centreMat));
	scene.Add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, leftMat));
	scene.Add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, rightMat));
}

void RedGreenScene(Scene& scene)
{
	auto leftMat = std::make_shared<DiffuseLambert>(Colour(0.0, 0.0, 1.0));
	auto rightMat = std::make_shared<DiffuseLambert>(Colour(1.0, 0.0, 0.0));

	double r = cos(pi / 4.0);

	scene.Add(std::make_shared<Sphere>(Point3(-r, 0.0, -1.0), r, leftMat));
	scene.Add(std::make_shared<Sphere>(Point3(r, 0.0, -1.0), r, rightMat));
}