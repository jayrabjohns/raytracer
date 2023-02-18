#include <iostream>
#include <string>
#include <thread>

#include "raytracer.hpp"
#include "../geometry/plane.hpp"
#include "../geometry/sphere.hpp"
#include "../utils/math_utils.hpp"

extern "C" {
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../../stb/stb_image_write.h"
}

double Raytracer::render_png(const ImageOptions& img_ops, const Scene& scene, const char* file_path, const bool use_single_thread) {
  int height = static_cast<int>((img_ops.width / scene.camera.get()->aspect_ratio));
  int colour_channels = 3;
  uint8_t* data = new uint8_t[img_ops.width * height * colour_channels];
  std::mutex data_mutex;
  RenderOptions render_ops(img_ops, height, scene, 0, height, data, data_mutex);

  double elapsed_secs = render(render_ops, data, use_single_thread);
  int result = stbi_write_png(file_path, render_ops.img_ops.width, height, colour_channels, data, render_ops.img_ops.width * colour_channels);
  if (!result) {
    std::cerr << "Failed writing image to " << file_path << std::endl;
  }

  delete[] data;
  return elapsed_secs;
}

double Raytracer::render(RenderOptions& render_ops, uint8_t* data, const bool use_single_thread) {
  unsigned int hardware_threads = std::thread::hardware_concurrency();
  unsigned int threads_num = (hardware_threads == 0 || use_single_thread ? 1 : hardware_threads);
  std::thread* threads = new std::thread[threads_num];

  time_t start, end;
  time(&start);

  int chunk_size = render_ops.height / threads_num;
  for (size_t i = 0; i < threads_num; ++i) {
    render_ops.start_row = i * chunk_size;
    render_ops.end_row = (i == threads_num - 1 ? render_ops.height : render_ops.start_row + chunk_size);
    threads[i] = std::thread(&Raytracer::render_chunk, render_ops);
  }

  for (size_t i = 0; i < threads_num; ++i) {
    threads[i].join();
  }
  time(&end);
  double elapsed_secs = static_cast<double>(end - start);

  delete[] threads;
  return elapsed_secs;
}

inline Colour get_background_colour(const Ray& ray) {
  Vector3 dir = normalise(ray.direction);
  double t = 0.5 * (dir.y() + 1.0);
  return (1.0 - t) * Colour(1.0, 1.0, 1.0) + t * Colour(0.5, 0.7, 1.0);
}

Colour Raytracer::get_ray_colour(const Ray& ray, const Scene& scene, const int max_depth) {
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

void Raytracer::render_chunk(RenderOptions render_ops) {
  uint8_t* chunk_data = new uint8_t[(render_ops.end_row - render_ops.start_row) * render_ops.img_ops.width * render_ops.img_ops.colour_channels]; // Each thread uses its own buffer to avoid loads of locking / unlocking shenanigans
  int index = 0;

  for (int i = render_ops.start_row; i < render_ops.end_row; ++i) {
    for (int j = 0; j < render_ops.img_ops.width; ++j) {
      Colour pixel_colour;
      for (size_t s = 0; s < render_ops.img_ops.samples_per_pixel; ++s) {
        double u = (j + random_double_01()) / (render_ops.img_ops.width - 1);
        double v = (i + random_double_01()) / (render_ops.height - 1);
        v = 1.0 - v; // Flipping image so +y is up

        Ray ray = render_ops.scene.camera.get()->ray_at(u, v);
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

      chunk_data[index++] = static_cast<uint8_t>(r);
      chunk_data[index++] = static_cast<uint8_t>(g);
      chunk_data[index++] = static_cast<uint8_t>(b);
    }
  }

  const int img_offset = render_ops.start_row * render_ops.img_ops.width * render_ops.img_ops.colour_channels;

  render_ops.data_mutex.lock();
  for (int i = 0; i < index; ++i) {
    int _i = i + img_offset;
    render_ops.data[_i] = chunk_data[i];
  }
  render_ops.data_mutex.unlock();

  delete[] chunk_data;
}
