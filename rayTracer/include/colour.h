#ifndef COLOUR_H
#define COLOUR_H

#include <vec3.h>
#include <ray.h>
#include <iostream>

void writeColour(std::ostream& out, colour pixelColour)
{
	out << static_cast<int>(255.999 * pixelColour.x()) << ' '
		<< static_cast<int>(255.999 * pixelColour.y()) << ' '
		<< static_cast<int>(255.999 * pixelColour.z()) << '\n';
}

colour rayColour(const ray& r)
{
	auto t = isRayHittingSphere(point3(0, 0, -1), 0.5, r);
	if (t > 0.0)
	{
		vec3 normal = unitVec(r.at(t) - vec3(0, 0, -1));
		normal = (normal * 0.5);
		return 0.5 * colour(normal.x() + 1, normal.y() + 1, normal.z() + 1);
	}
	vec3 unitDir = unitVec(r.direction());
	t = 0.5 * (unitDir.y() + 1.0);
	return (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);
}

#endif // !COLOUR_H

