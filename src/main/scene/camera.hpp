#ifndef CAMERA_H
#define CAMERA_H

#include "../geometry/vec3.hpp"
#include "../geometry/ray.hpp"

class Camera {
public:
  Vector3 cam_up;
  double view_port_width;
  double view_port_height;
  double aspect_ratio;
  double aperture;
  double focus_dist;
  double near_clipping_plane;
  double far_clipping_plane;

private:
  Vector3 looking_at;
  Point3 origin;
  Vector3 horizontal;
  Vector3 vertical;
  Point3 lower_left_corner;
  Vector3 u, v, w;
  double lens_radius;


public:
  Camera();
  void init(Point3 origin, Point3 look_at, Vector3 cam_up, double vertical_fov_degs, double aspect_ratio, double aperture, double focus_dist, double near_clipping_plane, double far_clipping_plane);

  Ray ray_at(double u, double v) const;

  void set_origin(Point3 origin);
  void look_at(Point3 point);
  void set_cam_up(Vector3 cam_up);
  void set_vertical_fov(double vfov);
  void set_aspect_ratio(double aspect_ratio);
};
#endif
