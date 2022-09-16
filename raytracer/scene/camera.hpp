#ifndef CAMERA_H
#define CAMERA_H

#include "../geometry/vec3.hpp"
#include "../geometry/ray.hpp"

class Camera
{
public:
	Vector3 camUp;
	double viewPortWidth;
	double viewPortHeight;
	double aspectRatio;
	double aperture;
	double focusDist;
	double nearClippingPlane;
	double farClippingPlane;

private:
	Vector3 lookAt;
	Point3 origin;
	Vector3 horizontal;
	Vector3 vertical;
	Point3 lowerLeftCorner;
	Vector3 u, v, w;
	double lensRadius;


public:
	Camera();
	Camera(const Point3 origin, const Point3 lookAt, const Vector3 camUp, double verticalFovDegs, double aspectRatio, double aperture, double focusDist, double nearClippingPlane, double farClippingPlane);
	void Init(const Point3 origin, const Point3 lookAt, const Vector3 camUp, double verticalFovDegs, double aspectRatio, double aperture, double focusDist, double nearClippingPlane, double farClippingPlane);

	Ray RayAt(double u, double v) const;

	void SetOrigin(const Point3 origin);
	void LookAt(const Point3 lookAt);
	void SetCamUp(const Vector3 camUp);
	void SetVerticalFov(const double vfov);
	void SetAspectRatio(const double aspectRatio);
};

#endif