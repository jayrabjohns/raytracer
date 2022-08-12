#include<iostream>

#include "raytracer.h"

int main()
{
	const int imageWidth = 400;
	const double aspectRatio = 16.0 / 9.0;
	const int numChannels = 3;
	const int quality = 100;

	Raytracer raytracer = Raytracer();
	raytracer.RenderDemo(imageWidth, aspectRatio, quality);

	std::cerr << "Done." << std::endl;

	return 0;
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