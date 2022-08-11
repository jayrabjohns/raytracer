// raytracer.cpp : Defines the entry point for the application.
//

#include "raytracer.h"

int main()
{
	const int imageWidth  = 256;
	const int imageHeight = 256;
	const int numChannels = 3;

	GenerateAndWriteJPG(imageWidth, imageHeight, numChannels);

	std::cout << "Done." << std::endl;
	return 0;
}

void GenerateAndWriteJPG(const int width, const int height, const int numChannels, const int quality)
{
	uint8_t *data = new uint8_t[width * height * numChannels];
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

std::string GetImagePPM(const int width, const int height)
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
