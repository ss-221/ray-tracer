#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

struct hitRecord
{
	point3 p;
	vec3 normal;
	double t;

	bool frontFace;

	inline void setFaceNormal(const ray& r, const vec3& outwardNormal)
	{
		frontFace = dot(r.direction(), outwardNormal) < 0;
		normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class hittable
{
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hitRecord& hitRec)	const = 0;
};
#endif // !HITTABLE_H
