#ifndef RAYTRACER_H
#define RAYTRACER_H

#include "image_options.hpp"
#include "render_options.hpp"
#include "execution_context.hpp"
#include "../geometry/ray.hpp"
#include "../scene/scene.hpp"
#include "../scene/camera.hpp"

class Raytracer {
public:
  Raytracer() {}
  virtual ~Raytracer() {}

  virtual void render(ImageOptions img_ops, Scene scene, uint8_t* data) const = 0;
  virtual void render_png(const ImageOptions& img_ops, const Scene& scene, const char* out_path) const = 0;
};
#endif 
