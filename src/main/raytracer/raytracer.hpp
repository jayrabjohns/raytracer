#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "../geometry/ray.hpp"
#include "../scene/scene.hpp"
#include "../scene/camera.hpp"

struct ImageOptions {
  const int width;
  const int height;
  const int samples_per_pixel;
  const int max_ray_bounces;
  const int colour_channels;

  ImageOptions(int width, int height, int samples_per_pixel, int max_ray_bounces, int colour_channels) :
    width(width),
    height(height),
    samples_per_pixel(samples_per_pixel),
    max_ray_bounces(max_ray_bounces),
    colour_channels(colour_channels) {}
};

class Raytracer {
public:
  Raytracer() {}
  virtual ~Raytracer() {}

  virtual void render(ImageOptions img_ops, Scene scene, uint8_t* data) const = 0;
  virtual void render_png(const ImageOptions& img_ops, const Scene& scene, const char* out_path) const = 0;
};
#endif 
