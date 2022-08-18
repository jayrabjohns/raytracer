#ifndef CAMERA_H
#define CAMERA_H

#include "geometry/vec3.hpp"
#include "geometry/ray.hpp"

class Camera
{
public:
	double ViewPortWidth;
	double ViewPortHeight;
	double AspectRatio;
	double NearClippingDistance;
	double FarClipingDistance;
	double FocalLegnth;

private:
	Point3 Origin;
	Vec3 Horizontal;
	Vec3 Vertical;
	Point3 LowerLeftCorner;


public:
	Camera();
	Camera(double viewPortHeight, double aspectRatio, double nearClippingDistance, double farClipingDistance, double focalLength, const Point3 origin);

	Ray RayAt(double u, double v) const;

	void SetOrigin(const Point3 origin);
};

#endif