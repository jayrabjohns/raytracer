#include<iostream>
#include<thread>

#include "raytracer/raytracer.hpp"
#include "raytracer/execution_context.hpp"
#include "raytracer/multi_threaded_cpu_raytracer.hpp"
#include "scene/demos.hpp"
#include "scene/scene.hpp"

extern "C" {
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../stb/stb_image_write.h"
}

const int expected_cpp_version = 201703;

int main() {
  if (__cplusplus != expected_cpp_version) {
    std::cerr << "Using incompatible version of C++. Expected " << expected_cpp_version << ", but the current version is " << __cplusplus << std::endl;
    return 1;
  }

  ImageOptions img_ops(200, 100, 32, 50, 3);

  double aspect_ratio = img_ops.width / static_cast<double>(img_ops.height);
  auto camera = std::make_shared<Camera>();
  camera->init(Point3(0.0, 0.0, 0.0), Point3(0.0, 0.0, -1.0), Vector3(0.0, 1.0, 0.0), 90.0, aspect_ratio, 0.0, 1.0, 0.0, infinity);

  Scene scene = Scene(camera);
  populate_scene_demo(scene);

  const unsigned int hardware_threads = std::thread::hardware_concurrency();
  CPUExecutionContext execution_context = CPUExecutionContext{ hardware_threads };
  auto raytracer = std::make_unique<MultiThreadedCPURaytracer>(execution_context);
  raytracer->render_png(img_ops, scene, "raytrace_out.png");

  std::cout << "\nDone." << std::endl;

  return 0;
}
