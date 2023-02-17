#include<iostream>

#include "raytracer/raytracer.hpp"
#include "scene/demos.hpp"
#include "scene/scene.hpp"

const int expectedCppVersion = 201703;

int main()
{
	if (__cplusplus != expectedCppVersion) 
	{
		std::cerr << "Using incompatible version of C++. Expected " << expectedCppVersion << ", but the current version is "  << __cplusplus << std::endl;
		return 1;
	}

	imageOptions imageOps(200, 32, 50, 3);

	auto camera = std::make_shared<Camera>();
	Scene scene = Scene(camera);
	DemoScene(scene);

	Raytracer raytracer = Raytracer();
	double elapsedSecs = raytracer.RenderPng(imageOps, scene, "raytrace_out.png");

	std::cout << "\nDone." << std::endl;
	std::cout << "Total time: " << elapsedSecs << 's' << std::endl;
	return 0;
}
