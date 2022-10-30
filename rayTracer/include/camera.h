#ifndef CAMERA_H
#define CAMERA_H

#include <utils.h>

class camera
{
public:
	camera()
	{
		origin = point3(0, 0, 0);
		auto viewPortHeight = 2.0;
		auto viewPortWidth = viewPortHeight * aspectRatio;
		auto focalLen = 1.0;
		vertical = vec3(0.0, viewPortHeight, 0.0);
		horizontal = vec3(viewPortWidth, 0.0, 0.0);
		lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLen);
	}

	ray getRay(double u, double v)	const
	{
		return ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}

private:
	point3 origin, lowerLeftCorner;
	vec3 horizontal, vertical;
};

#endif // !CAMERA_H

