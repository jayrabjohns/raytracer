// raytracer.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include "geometry/scene.hpp"
#include "camera.hpp"

void RandomScene(Scene& scene, Camera* camera);
void DemoScene(Scene& scene, Camera* camera);
void RedGreenScene(Scene& scene, Camera* camera);