#ifndef MULTI_THREADED_CPU_RAYTRACER_H
#define MULTI_THREADED_CPU_RAYTRACER_H

#include "./raytracer.hpp"

class MultiThreadedCPURaytracer : public Raytracer {
public:
  MultiThreadedCPURaytracer(unsigned int threads_num);

  void render(ImageOptions img_ops, Scene scene, uint8_t* data) const;
  void render_png(const ImageOptions& img_ops, const Scene& scene, const char* out_path) const;

private:
  const unsigned int threads_num;

  void render_chunk(const ImageOptions& img_ops, const Scene& scene, int start_row, int end_row, uint8_t* data) const;
  Colour get_ray_colour(const Ray& ray, const Scene& scene, int max_depth) const;
  Colour get_background_colour(const Ray& ray) const;
};
#endif
