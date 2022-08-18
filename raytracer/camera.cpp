#include "camera.hpp"
#include "utils/math_utils.hpp"

Camera::Camera() : Camera::Camera(2.0, 16.0 / 9.0, 0.0, infinity, 1.0, Point3()) {}

Camera::Camera(double viewPortHeight, double aspectRatio, double nearClippingDistance, double farClipingDistance, double focalLength, const Point3 origin)
{
	ViewPortHeight = viewPortHeight;
	AspectRatio = aspectRatio;
	ViewPortWidth = AspectRatio * ViewPortHeight;
	NearClippingDistance = nearClippingDistance;
	FarClipingDistance = farClipingDistance;
	FocalLegnth = focalLength;

	Horizontal = Vec3(ViewPortWidth, 0.0, 0.0);
	Vertical = Vec3(0.0, ViewPortHeight, 0.0);
	SetOrigin(origin);
}

void Camera::SetOrigin(const Point3 origin)
{
	Origin = origin;
	LowerLeftCorner = Origin - (Horizontal * 0.5) - (Vertical * 0.5) - Vec3(0.0, 0.0, FocalLegnth);
}

Ray Camera::RayAt(double u, double v) const
{
	return Ray(Origin, LowerLeftCorner + (u * Horizontal) + (v * Vertical) - Origin);
}
