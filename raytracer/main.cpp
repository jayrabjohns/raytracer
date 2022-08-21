#include<iostream>

#include "main.hpp"
#include "raytracer.hpp"
#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"

#include "materials/diffuse_lambert.hpp"
#include "materials/metal.hpp"

int main()
{
	int width = 800;
	double aspectRatio = 16.0 / 9.0;
	int samplesPerPixel = 32;
	int maxRayDepth = 50;

	auto camera = std::make_shared<Camera>();
	Scene scene = Scene(camera);
	DemoScene(scene, camera.get());

	Raytracer raytracer = Raytracer();
	raytracer.Render(width, aspectRatio, samplesPerPixel, maxRayDepth, scene);

	std::cerr << "\nDone." << std::endl;
	return 0;
}

void DemoScene(Scene& scene, Camera* camera)
{
	auto groundMat = std::make_shared<DiffuseLambert>(Colour(0.8, 0.8, 0.0));
	auto centreMat = std::make_shared<DiffuseLambert>(Colour(0.7, 0.3, 0.3));
	auto leftMat = std::make_shared<Metal>(Colour(0.8, 0.8, 0.8), 0.8);
	auto rightMat = std::make_shared<Metal>(Colour(0.8, 0.6, 0.2));

	scene.Add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, groundMat));
	scene.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, centreMat));
	scene.Add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, leftMat));
	scene.Add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, rightMat));

	camera->SetOrigin(Point3(0.0, 0.0, 0.0));
}
