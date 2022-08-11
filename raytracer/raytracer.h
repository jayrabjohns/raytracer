// raytracer.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <string>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void GenerateAndWriteJPG(const int width, const int height, const int numChannels, const int quality = 100);
std::string GetImagePPM(const int width, const int height);
