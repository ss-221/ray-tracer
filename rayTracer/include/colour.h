#ifndef COLOUR_H
#define COLOUR_H

#include <iostream>
#include <utils.h>
#include <sphere.h>

void writeColour(std::ostream& out, colour pixelColour)
{
	out << static_cast<int>(255.999 * pixelColour.x()) << ' '
		<< static_cast<int>(255.999 * pixelColour.y()) << ' '
		<< static_cast<int>(255.999 * pixelColour.z()) << '\n';
}

colour rayColour(const ray& r, const hittable& world)
{
	hitRecord rec;
	if (world.hit(r, 0, infinity, rec))
	{
		return 0.5 * (rec.normal + colour(1, 1, 1));
	}

	vec3 unitDir = unitVec(r.direction());
	auto t = 0.5 * (unitDir.y() + 1.0);
	return (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);
}

#endif // !COLOUR_H

