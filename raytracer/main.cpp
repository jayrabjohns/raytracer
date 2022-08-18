#include<iostream>

#include "main.hpp"
#include "raytracer.hpp"
#include "geometry/plane.hpp"
#include "geometry/sphere.hpp"

int main()
{
	int width = 800;
	double aspectRatio = 16.0 / 9.0;
	int samplesPerPixel = 4;

	auto camera = std::make_shared<Camera>();
	Scene scene = Scene(camera);
	DemoScene(scene, camera.get());

	Raytracer raytracer = Raytracer();
	raytracer.Render(width, aspectRatio, samplesPerPixel, scene);

	std::cerr << "Done." << std::endl;
	return 0;
}

void DemoScene(Scene& scene, Camera* camera)
{
	scene.Add(std::make_shared<Plane>(Point3(1.0, -5.0, 0.0), Point3(0.0, -5.0, 0.0), Point3(0.0, -5.0, -1.0)));
	scene.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5));

	camera->SetOrigin(Point3(0.0, 0.0, 0.0));
}
