#include<iostream>

#include "main.h"
#include "raytracer.h"

int main()
{
	CircleDemo();
	return 0;
}

void CircleDemo()
{
	Raytracer raytracer = Raytracer();
	raytracer.CircleDemo();

	std::cerr << "Done." << std::endl;
}

void JpegDemo()
{
	const int imageWidth = 256;
	const int imageHeight = 256;
	const int numChannels = 3;

	Raytracer raytracer = Raytracer();
	raytracer.GenerateAndWriteJPGDemo(imageWidth, imageHeight, numChannels);

	std::cerr << "Done." << std::endl;
}