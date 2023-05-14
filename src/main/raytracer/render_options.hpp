#ifndef RENDER_OPTIONS_H
#define RENDER_OPTIONS_H

#include "image_options.hpp"
#include "../scene/scene.hpp"

struct RenderOptions {
  const ImageOptions& img_ops;
  const Scene& scene;
  const int start_row;
  const int end_row;

  RenderOptions(const ImageOptions& img_ops, const Scene& scene, int start_row, int end_row):
    img_ops(img_ops),
    scene(scene),
    start_row(start_row),
    end_row(end_row) {}
};
#endif
