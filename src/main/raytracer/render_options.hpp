#ifndef RENDER_OPTIONS_H
#define RENDER_OPTIONS_H

#include <mutex>

#include "image_options.hpp"
#include "../scene/scene.hpp"

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
#endif
