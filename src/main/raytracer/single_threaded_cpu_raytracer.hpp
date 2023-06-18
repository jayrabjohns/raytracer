#ifndef SINGLE_THREADED_CPU_RAYTRACER_H
#define SINGLE_THREADED_CPU_RAYTRACER_H

#include "./raytracer.hpp"

class SingleThreadedCPURaytracer : public Raytracer {
public:
  SingleThreadedCPURaytracer();

  void render(ImageOptions img_ops, Scene scene, uint8_t* data) const override;
  void render_png(const ImageOptions& img_ops, const Scene& scene, const char* out_path) const override;

private:
  Colour get_background_colour(const Ray& ray) const;
  Colour get_ray_colour(const Ray& ray, const Scene& scene, const int max_depth) const;
};
#endif
