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
	const int imageWidth = 400;
	const double aspectRatio = 16.0 / 9.0;
	const int numChannels = 3;
	const int quality = 100;

	Raytracer raytracer = Raytracer();
	raytracer.CircleDemo(imageWidth, aspectRatio, quality);

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