#include <iostream>
#include <string>
#include <thread>
#include <functional>

#include "raytracer.hpp"
#include "../geometry/plane.hpp"
#include "../geometry/sphere.hpp"
#include "../utils/math_utils.hpp"

extern "C" {
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../../stb/stb_image_write.h"
}

// #ifdef DEBUG
#include "../../../perf/timer/timer_utils.hpp"
// #endif

Raytracer::Raytracer() {
  const unsigned int hardware_threads = std::thread::hardware_concurrency();
  this->threads_num = (hardware_threads == 0 ? 1 : hardware_threads);
}

void Raytracer::render_png(const ImageOptions& img_ops, const Scene& scene, const char* file_path, const bool use_single_thread) const {
  const int colour_channels = 3;
  uint8_t* data = new uint8_t[img_ops.width * img_ops.height * colour_channels];

#ifdef TIMER_ENABLED
  double elapsed_secs = timeFn([this, img_ops, data, scene]() {
    Raytracer::render(img_ops, scene, data);
  });
  std::cout << "Render completed in " << elapsed_secs << 's' << std::endl;
#else
  render(render_ops, data, use_single_thread);
  std::cout << "Render complete" << std::endl;
#endif

  const int result = stbi_write_png(file_path, img_ops.width, img_ops.height, colour_channels, data, img_ops.width * colour_channels);
  if (!result) {
    std::cerr << "Failed writing image to " << file_path << std::endl;
  }

  delete[] data;
}

void Raytracer::render(const ImageOptions img_ops, const Scene scene, uint8_t* data) const {
  std::thread* threads = new std::thread[threads_num];

  const int chunk_size = img_ops.height / threads_num;
  for (size_t i = 0; i < threads_num; ++i) {
    const int start_row = i * chunk_size;
    const int end_row = (i == threads_num - 1 ? img_ops.height : start_row + chunk_size);
    const RenderOptions render_ops = RenderOptions(img_ops, scene, start_row, end_row);

    threads[i] = std::thread([this, render_ops, data]() {
      Raytracer::render_chunk(render_ops, data);
    });
  }

  for (size_t i = 0; i < threads_num; ++i) {
    threads[i].join();
  }

  delete[] threads;
}

void Raytracer::render_chunk(RenderOptions render_ops, uint8_t* data) const {
  uint8_t* chunk_data = new uint8_t[(render_ops.end_row - render_ops.start_row) * render_ops.img_ops.width * render_ops.img_ops.colour_channels]; // Each thread uses its own buffer to avoid loads of locking / unlocking shenanigans
  int chunk_index = 0;

  for (int i = render_ops.start_row; i < render_ops.end_row; ++i) {
    for (int j = 0; j < render_ops.img_ops.width; ++j) {
      Colour pixel_colour;
      for (size_t s = 0; s < render_ops.img_ops.samples_per_pixel; ++s) {
        const double u = (j + random_double_01()) / (render_ops.img_ops.width - 1);
        const double v = 1.0 - (i + random_double_01()) / (render_ops.img_ops.height - 1);
        // 1.0 - v to flip the image, so that +y is up

        const Ray ray = render_ops.scene.camera.get()->ray_at(u, v);
        pixel_colour += get_ray_colour(ray, render_ops.scene, render_ops.img_ops.max_ray_bounces);
      }

      pixel_colour /= render_ops.img_ops.samples_per_pixel;

      // Gamma-correct for gamma = 2.0
      double r = std::sqrt(pixel_colour.x());
      double g = std::sqrt(pixel_colour.y());
      double b = std::sqrt(pixel_colour.z());

      r = 256.0 * clamp(r, 0.0, 0.999);
      g = 256.0 * clamp(g, 0.0, 0.999);
      b = 256.0 * clamp(b, 0.0, 0.999);

      chunk_data[chunk_index++] = static_cast<uint8_t>(r);
      chunk_data[chunk_index++] = static_cast<uint8_t>(g);
      chunk_data[chunk_index++] = static_cast<uint8_t>(b);
    }
  }

  const int img_offset = render_ops.start_row * render_ops.img_ops.width * render_ops.img_ops.colour_channels;
  for (int i = 0; i < chunk_index; ++i) {
    const int data_index = i + img_offset;
    data[data_index] = chunk_data[i];
  }

  delete[] chunk_data;
}

inline Colour get_background_colour(const Ray& ray) {
  Vector3 dir = normalise(ray.direction);
  const double t = 0.5 * (dir.y() + 1.0);
  return (1.0 - t) * Colour(1.0, 1.0, 1.0) + t * Colour(0.5, 0.7, 1.0);
}

Colour Raytracer::get_ray_colour(const Ray& ray, const Scene& scene, const int max_depth) const {
  Ray r = ray;
  Colour ray_colour = get_background_colour(r);

  bool hit = false;
  Ray scattered;
  Colour attenuation;
  HitRecord hit_record;
  for (int depth = 0; depth < max_depth; ++depth) {
    if (depth == max_depth) { return Colour(0.0, 0.0, 0.0); }
    else if (scene.is_hit(r, 0.001, infinity, hit_record)) {
      hit = true;
      if (hit_record.material->scatter(r, hit_record, attenuation, scattered)) {
        r = scattered;
        ray_colour *= attenuation;
      }
    }
    else break;
  }

  return ray_colour;
}
