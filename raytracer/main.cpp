#include<iostream>

#include "main.h"
#include "raytracer.h"
#include "geometry/plane.h"
#include "geometry/sphere.h"

int main()
{
	int width = 800;
	double aspectRatio = 16.0 / 9.0;

	Scene scene;
	GetCircleDemoScene(scene);

	Raytracer raytracer = Raytracer();
	raytracer.Render(width, aspectRatio, scene);

	std::cerr << "Done." << std::endl;
	return 0;
}

void GetCircleDemoScene(Scene& scene)
{
	scene.Add(std::make_shared<Plane>(Point3(1.0, -5.0, 0.0), Point3(0.0, -5.0, 0.0), Point3(0.0, -5.0, -1.0)));
	scene.Add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5));
}
