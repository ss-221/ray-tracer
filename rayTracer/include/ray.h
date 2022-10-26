#ifndef RAY_H
#define RAY_H

#include <vec3.h>

class ray
{

public:
	ray() {};
	ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}
	point3 origin() const { return orig; }
	vec3 direction() const { return dir; }

	point3 at(double t) const
	{
		return orig + dir * t;
	}

private:
	point3 orig;
	vec3 dir;
};

double isRayHittingSphere(const point3& center, double radius, const ray& r)
{
	vec3 adjustedCenter = r.origin() - center;
	auto a = dot(r.direction(), r.direction());
	auto b = 2.0 * dot(adjustedCenter, r.direction());
	auto c = dot(adjustedCenter, adjustedCenter) - radius * radius;

	auto discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return (-b - sqrt(discriminant)) / (2.0 * a);
	}
}

#endif // !RAY_H
