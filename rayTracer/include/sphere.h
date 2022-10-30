#ifndef SPHERE_H
#define SPHERE_H

#include <hittable.h>
#include <vec3.h>

class sphere : public hittable
{
public:
	sphere() {}
	sphere(point3 cen, double rad) : center(cen), radius(rad) {}

	virtual bool hit(const ray& r, double t_min, double t_max, hitRecord& hitRec) const override;

private:
	point3 center;
	double radius = 0.0;
};

#endif // !SPHERE_H
