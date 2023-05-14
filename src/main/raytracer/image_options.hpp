#ifndef IMAGE_OPTIONS_H
#define IMAGE_OPTIONS_H

struct ImageOptions {
  const int width;
  const int height;
  const int samples_per_pixel;
  const int max_ray_bounces;
  const int colour_channels;

  ImageOptions(int width, int height, int samples_per_pixel, int max_ray_bounces, int colour_channels):
    width(width),
    height(height),
    samples_per_pixel(samples_per_pixel),
    max_ray_bounces(max_ray_bounces),
    colour_channels(colour_channels) {}
};
#endif
