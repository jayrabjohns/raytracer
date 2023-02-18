#ifndef DEMOS_H
#define DEMOS_H

#include <memory>

#include "../scene/scene.hpp"
#include "../geometry/sphere.hpp"
#include "../materials/diffuse_lambert.hpp"
#include "../materials/metal.hpp"
#include "../materials/dielectric.hpp"

// #include "../geometry/sphere.hpp"

std::shared_ptr<Sphere> gen_random_sphere(double x, double y, double z, double x_leeway, double y_leeway, double z_leeway, double radius) {
  Point3 centre(x + x_leeway * random_double_01(), y + y_leeway * random_double_01(), z + z_leeway * random_double_01());

  double choose_mat = random_double_01();
  if (choose_mat <= 0.80) {
    Colour albedo = Colour::random_01() * Colour::random_01();
    auto sphere_mat = std::make_shared<DiffuseLambert>(albedo);
    return std::make_shared<Sphere>(centre, radius, sphere_mat);
  }
  else if (choose_mat <= 0.95) {
    Colour albedo = Colour::random(0.5, 1.0);
    double fuzz = random_double(0.0, 0.5);
    auto sphere_mat = std::make_shared<Metal>(albedo, fuzz);
    return std::make_shared<Sphere>(centre, radius, sphere_mat);
  }
  else {
    auto sphere_mat = std::make_shared<Dielectric>(random_double(0.5, 1.5));
    return std::make_shared<Sphere>(centre, radius, sphere_mat);
  }
}

void random_scene(Scene& scene) {
  // Camera
  Point3 look_from = Point3(13.0, 2.0, 3.0);
  Point3 look_at = Point3(0.0, 0.0, 0.0);
  Point3 cam_up = Point3(0.0, 1.0, 0.0);
  double v_fov = 20.0;
  double aspect_ratio = 3.0 / 2.0;
  double aperture = 0.1;
  double dist_to_focus = 10.0;

  scene.camera.get()->init(look_from, look_at, cam_up, v_fov, aspect_ratio, aperture, dist_to_focus, 0.0, infinity);

  // Scene
  auto ground_mat = std::make_shared<DiffuseLambert>(Colour(0.5, 0.5, 0.5));
  auto ground = std::make_shared<Sphere>(Point3(0.0, -1000.0, 0.0), 1000.0, ground_mat);
  scene.add(ground);

  for (int x = -11; x < 11; ++x) {
    for (int z = -11; z < 11; ++z) {
      auto random_sphere = gen_random_sphere(x, 0.2, z, 0.9, 0.0, 0.9, 0.2);
      if ((random_sphere.get()->centre - Point3(4.0, 0.2, 0.0)).length() > 0.9) {
        scene.add(random_sphere);
      }
    }
  }

  auto mat1 = std::make_shared<Dielectric>(1.5);
  auto sphere1 = std::make_shared<Sphere>(Point3(0.0, 1.0, 0.0), 1.0, mat1);
  scene.add(sphere1);

  auto mat2 = std::make_shared<DiffuseLambert>(Colour(0.4, 0.2, 0.1));
  auto sphere2 = std::make_shared<Sphere>(Point3(-4.0, 1.0, 0.0), 1.0, mat2);
  scene.add(sphere2);

  auto mat3 = std::make_shared<Metal>(Colour(0.7, 0.6, 0.5), 0.0);
  auto sphere3 = std::make_shared<Sphere>(Point3(4.0, 1.0, 0.0), 1.0, mat3);
  scene.add(sphere3);
}

void demo_scene(Scene& scene) {
  auto ground_mat = std::make_shared<DiffuseLambert>(Colour(0.8, 0.8, 0.0));
  //auto backMat = std::make_shared<DiffuseLambert>(Colour(0.7, 0.3, 0.3));
  auto centre_mat = std::make_shared<Dielectric>(1.5);
  auto left_mat = std::make_shared<Metal>(Colour(0.8, 0.8, 0.8), 0.8);
  auto right_mat = std::make_shared<Metal>(Colour(0.8, 0.6, 0.2));

  scene.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, ground_mat));
  //scene.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.2), 0.5, backMat));
  scene.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, centre_mat));
  scene.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), -0.4, centre_mat));
  scene.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, left_mat));
  scene.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, right_mat));
}

void red_green_scene(Scene& scene) {
  auto left_mat = std::make_shared<DiffuseLambert>(Colour(0.0, 0.0, 1.0));
  auto right_mat = std::make_shared<DiffuseLambert>(Colour(1.0, 0.0, 0.0));

  double r = cos(pi / 4.0);

  scene.add(std::make_shared<Sphere>(Point3(-r, 0.0, -1.0), r, left_mat));
  scene.add(std::make_shared<Sphere>(Point3(r, 0.0, -1.0), r, right_mat));
}

#endif
