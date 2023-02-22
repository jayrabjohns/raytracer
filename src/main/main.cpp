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

  ImageOptions img_ops(640, 360, 32, 50, 3);

  auto camera = std::make_shared<Camera>();

  double aspect_ratio = img_ops.width / static_cast<double>(img_ops.height);
  camera.get()->init(Point3(0.0, 0.0, 0.0), Point3(0.0, 0.0, -1.0), Vector3(0.0, 1.0, 0.0), 90.0, aspect_ratio, 0.0, 1.0, 0.0, infinity);

  Scene scene = Scene(camera);
  populate_scene_demo(scene);

  Raytracer raytracer = Raytracer();
  raytracer.render_png(img_ops, scene, "raytrace_out.png");

  std::cout << "\nDone." << std::endl;
  return 0;
}
