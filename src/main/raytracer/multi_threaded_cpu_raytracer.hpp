#ifndef MULTI_THREADED_CPU_RAYTRACER_H
#define MULTI_THREADED_CPU_RAYTRACER_H

#include "./raytracer.hpp"
#include "./execution_context.hpp"

class MultiThreadedCPURaytracer: public Raytracer {
public:
  MultiThreadedCPURaytracer(CPUExecutionContext context);

  void render(ImageOptions img_ops, Scene scene, uint8_t* data) const;
  void render_png(const ImageOptions& img_ops, const Scene& scene, const char* out_path) const;

private:
  CPUExecutionContext execution_context;
};
#endif
