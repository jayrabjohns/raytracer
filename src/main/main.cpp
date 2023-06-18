#include<iostream>
#include<thread>

#include "raytracer/raytracer.hpp"
#include "raytracer/multi_threaded_cpu_raytracer.hpp"
#include "scene/demos.hpp"
#include "scene/scene.hpp"

extern "C" {
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
}

int main() {
  ImageOptions img_ops(600, 300, 32, 50, 3);

  double aspect_ratio = img_ops.width / static_cast<double>(img_ops.height);
  auto camera = std::make_shared<Camera>();
  camera->init(Point3(0.0, 0.0, 0.0), Point3(0.0, 0.0, -1.0), Vector3(0.0, 1.0, 0.0), 90.0, aspect_ratio, 0.0, 1.0, 0.0, infinity);

  Scene scene = Scene(camera);
  populate_scene_demo(scene);

  const unsigned int num_hardware_threads = std::thread::hardware_concurrency();
  auto raytracer = std::make_unique<MultiThreadedCPURaytracer>(num_hardware_threads);
  raytracer->render_png(img_ops, scene, "raytrace_out.png");

  std::cout << "\nDone." << std::endl;

  return 0;
}
