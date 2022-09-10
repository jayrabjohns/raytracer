#include "camera.hpp"
#include "utils/math_utils.hpp"

Camera::Camera() : Camera::Camera(Point3(0.0, 0.0, 0.0), Point3(0.0, 0.0, -1.0), Vector3(0.0, 1.0, 0.0), 90.0, 16.0 / 9.0, 0.0, 1.0, 0.0, infinity) {}

Camera::Camera(const Point3 origin, const Point3 lookAt, const Vector3 camUp, double verticalFovDegs, double aspectRatio, double aperture, double focusDist, double nearClippingPlane, double farClippingPlane)
{
	Init(origin, lookAt, camUp, verticalFovDegs, aspectRatio, aperture, focusDist, nearClippingPlane, farClippingPlane);
}

void Camera::Init(const Point3 origin, const Point3 lookAt, const Vector3 camUp, double verticalFovDegs, double aspectRatio, double aperture, double focusDist, double nearClippingPlane, double farClippingPlane)
{
	this->camUp = camUp;
	this->aspectRatio = aspectRatio;
	this->aperture = aperture;
	this->focusDist = focusDist;
	this->nearClippingPlane = nearClippingPlane;
	this->farClippingPlane = farClippingPlane;

	SetOrigin(origin);
	SetVerticalFov(verticalFovDegs);
	LookAt(lookAt);
}

void Camera::SetOrigin(const Point3 origin)
{
	this->origin = origin;
	lowerLeftCorner = origin - (horizontal * 0.5) - (vertical * 0.5) - origin;
}

void Camera::LookAt(const Point3 lookAt)
{
	this->lookAt = lookAt;

	w = (origin - lookAt).Normalised();
	u = cross(camUp, w).Normalised();
	v = cross(w, u);

	horizontal = focusDist * viewPortWidth * u;
	vertical = focusDist * viewPortHeight * v;
	lowerLeftCorner = origin - (horizontal * 0.5) - (vertical * 0.5) - (focusDist * w);

	lensRadius = aperture * 0.5;
}

void Camera::SetCamUp(const Vector3 camUp)
{
	this->camUp = camUp;
}

void Camera::SetVerticalFov(const double vfov)
{
	double h = tan(0.5 * DegToRad(vfov));

	this->viewPortHeight = 2.0 * h;
	this->viewPortWidth = aspectRatio * viewPortHeight;
}

void Camera::SetAspectRatio(const double aspectRatio)
{
	this->aspectRatio = aspectRatio;
}

inline Point3 RandomPointOnUnitDisk()
{
	return Point3(RandomDouble01(), RandomDouble01(), 0.0).Normalised();
}

Ray Camera::RayAt(double _u, double _v) const
{
	Point3 pointOnLens = lensRadius * RandomPointOnUnitDisk();
	Vector3 offset = u * pointOnLens.x() + v * pointOnLens.y();

	return Ray(
		origin + offset,
		lowerLeftCorner + (_u * horizontal) + (_v * vertical) - origin - offset);
}
