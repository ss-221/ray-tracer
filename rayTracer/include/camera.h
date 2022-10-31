#ifndef CAMERA_H
#define CAMERA_H

#include <utils.h>

class camera
{
public:
	camera(point3 lookFrom, point3 lookAt, vec3 viewUp, double fov, double aspectRatio, double aperture, double focusDist)
	{
		auto theta = degreesToRadians(fov);
		auto h = tan(theta / 2);
		auto viewPortHeight = 2.0 * h;
		auto viewPortWidth = viewPortHeight * aspectRatio;

		w = unitVec(lookFrom - lookAt);
		u = unitVec(cross(viewUp, w));
		v = cross(w, u);

		origin = lookFrom;		
		horizontal = focusDist* viewPortWidth * u;
		vertical = focusDist * viewPortHeight * v;
		lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - focusDist * w;
		lensRadius = aperture / 2;
	}

	ray getRay(double u, double v)	const
	{
		return ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
	}

private:
	point3 origin, lowerLeftCorner;
	vec3 horizontal, vertical, u, v, w;
	double lensRadius;
};

#endif // !CAMERA_H

