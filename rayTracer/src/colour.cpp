#include <colour.h>
#include <material.h>

class material;

double clamp(double x, double min, double max)
{
	if (x < min)	return min;
	if (x > max)	return max;
	return x;
}

void writeColour(std::ostream& out, const colour& pixelColour, const int& samplesPerPixel)
{

	auto R = pixelColour.x();
	auto G = pixelColour.y();
	auto B = pixelColour.z();

	auto scale = 1.0 / samplesPerPixel;
	R = sqrt(scale * R);
	G = sqrt(scale * G);
	B = sqrt(scale * B);

	out << static_cast<int>(256 * clamp(R, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(G, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * clamp(B, 0.0, 0.999)) << '\n';
}

colour rayColour(const ray& r, const hittable& world, int depth)
{
	hitRecord rec;
	if (depth <= 0)
	{
		return colour(0, 0, 0);
	}
	if (world.hit(r, 0.001, infinity, rec))
	{
		ray scattered;
		colour attenuation;
		if (rec.matPtr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * rayColour(scattered, world, depth - 1);
		}
		return colour(0, 0, 0);
	}

	vec3 unitDir = unitVec(r.direction());
	auto t = 0.5 * (unitDir.y() + 1.0);
	return (1.0 - t) * colour(1.0, 1.0, 1.0) + t * colour(0.5, 0.7, 1.0);
}