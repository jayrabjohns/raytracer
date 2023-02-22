#include "camera.hpp"
#include "../utils/math_utils.hpp"

Camera::Camera() {
  init(Point3(0.0, 0.0, 0.0), Point3(0.0, 0.0, -1.0), Vector3(0.0, 1.0, 0.0), 90.0, 16.0 / 9.0, 0.0, 1.0, 0.0, infinity);
}

void Camera::init(const Point3 origin, const Point3 look_at, const Vector3 cam_up, double vertical_fov_degs, double aspect_ratio, double aperture, double focus_dist, double near_clipping_plane, double far_clipping_plane) {
  this->cam_up = cam_up;
  this->aspect_ratio = aspect_ratio;
  this->aperture = aperture;
  this->focus_dist = focus_dist;
  this->near_clipping_plane = near_clipping_plane;
  this->far_clipping_plane = far_clipping_plane;

  set_origin(origin);
  set_vertical_fov(vertical_fov_degs);
  this->look_at(look_at);
}

void Camera::set_origin(const Point3 origin) {
  this->origin = origin;
  lower_left_corner = origin - (horizontal * 0.5) - (vertical * 0.5) - origin;
}

void Camera::look_at(const Point3 point) {
  this->looking_at = point;

  w = (origin - point).normalise();
  u = cross(cam_up, w).normalise();
  v = cross(w, u);

  horizontal = focus_dist * view_port_width * u;
  vertical = focus_dist * view_port_height * v;
  lower_left_corner = origin - (horizontal * 0.5) - (vertical * 0.5) - (focus_dist * w);

  lens_radius = aperture * 0.5;
}

void Camera::set_cam_up(const Vector3 cam_up) {
  this->cam_up = cam_up;
}

void Camera::set_vertical_fov(const double vfov) {
  double h = tan(0.5 * deg_to_rad(vfov));

  this->view_port_height = 2.0 * h;
  this->view_port_width = aspect_ratio * view_port_height;
}

void Camera::set_aspect_ratio(const double aspect_ratio) {
  this->aspect_ratio = aspect_ratio;
}

inline Point3 random_point_on_unit_disk() {
  return Point3(random_double_01(), random_double_01(), 0.0).normalise();
}

Ray Camera::ray_at(double u, double v) const {
  Point3 point_on_lens = lens_radius * random_point_on_unit_disk();
  Vector3 offset = this->u * point_on_lens.x() + this->v * point_on_lens.y();

  return Ray(
    origin + offset,
    lower_left_corner + (u * horizontal) + (v * vertical) - origin - offset);
}
