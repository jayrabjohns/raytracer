#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "image_options.hpp"
#include "render_options.hpp"
#include "../geometry/ray.hpp"
#include "../scene/scene.hpp"
#include "../scene/camera.hpp"

class Raytracer {
public:
  Raytracer();

  void render(ImageOptions img_ops, Scene scene, uint8_t* data) const;
  void render_png(const ImageOptions& img_ops, const Scene& scene, const char* out_path) const;

private:
  unsigned int threads_num;

  Colour get_ray_colour(const Ray& ray, const Scene& scene, int max_depth) const;
  void render_chunk(RenderOptions render_ops, uint8_t* data) const;
};
#endif 
