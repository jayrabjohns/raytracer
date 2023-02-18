#include<iostream>

#include "raytracer/raytracer.hpp"
#include "scene/demos.hpp"
#include "scene/scene.hpp"

const int expected_cpp_version = 201703;

int main() {
  if (__cplusplus != expected_cpp_version) {
    std::cerr << "Using incompatible version of C++. Expected " << expected_cpp_version << ", but the current version is " << __cplusplus << std::endl;
    return 1;
  }

  ImageOptions img_ops(200, 32, 50, 3);

  auto camera = std::make_shared<Camera>();
  Scene scene = Scene(camera);
  demo_scene(scene);

  Raytracer raytracer = Raytracer();
  double elapsed_secs = raytracer.render_png(img_ops, scene, "raytrace_out.png");

  std::cout << "\nDone." << std::endl;
  std::cout << "Total time: " << elapsed_secs << 's' << std::endl;
  return 0;
}
