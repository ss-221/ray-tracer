#ifndef CAMERA_H
#define CAMERA_H

#include <utils.h>

class camera
{
public:
	camera(point3 lookFrom, point3 lookAt, vec3 viewUp, double fov, double aspectRatio)
	{
		auto theta = degreesToRadians(fov);
		auto h = tan(theta / 2);
		auto viewPortHeight = 2.0 * h;
		auto viewPortWidth = viewPortHeight * aspectRatio;

		auto w = unitVec(lookFrom - lookAt);
		auto u = unitVec(cross(viewUp, w));
		auto v = cross(w, u);

		origin = lookFrom;		
		horizontal = viewPortWidth * u;
		vertical = viewPortHeight * v;
		lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - w;
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

