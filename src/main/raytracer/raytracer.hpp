#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "image_options.hpp"
#include "render_options.hpp"
#include "../geometry/ray.hpp"
#include "../scene/scene.hpp"
#include "../scene/camera.hpp"

class Raytracer {
public:
  double render(RenderOptions& render_ops, uint8_t* data, const bool use_single_thread = false);
  double render_png(const ImageOptions& img_ops, const Scene& scene, const char* file_path, const bool use_single_thread = false);

private:
  static Colour get_ray_colour(const Ray& ray, const Scene& scene, const int max_depth);
  static void render_chunk(RenderOptions render_ops);
};
#endif 
