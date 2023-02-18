#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <mutex>

#include "../geometry/ray.hpp"
#include "../scene/scene.hpp"
#include "../scene/camera.hpp"

struct ImageOptions {
  const int width;
  const int samples_per_pixel;
  const int max_ray_bounces;
  const int colour_channels;

  ImageOptions(const int width, const int samples_per_pixel, const int max_ray_bounces, const int colour_channels): width(width), samples_per_pixel(samples_per_pixel), max_ray_bounces(max_ray_bounces), colour_channels(colour_channels) {}
};

struct RenderOptions {
  const ImageOptions& img_ops;
  const int height;
  const Scene& scene;
  int start_row;
  int end_row;
  uint8_t* data;
  std::mutex& data_mutex;

  RenderOptions(const ImageOptions& img_ops, int height, const Scene& scene, int start_row, int end_row, uint8_t* data, std::mutex& data_mutex): img_ops(img_ops), height(height), scene(scene), start_row(start_row), end_row(end_row), data(data), data_mutex(data_mutex) {}
};

class Raytracer {
public:
  double render(RenderOptions& render_ops, uint8_t* data, const bool use_single_thread = false);
  double render_png(const ImageOptions& img_ops, const Scene& scene, const char* file_path, const bool use_single_thread = false);

private:
  static Colour get_ray_colour(const Ray& ray, const Scene& scene, const int max_depth);
  static void render_chunk(RenderOptions render_ops);
};
#endif 
