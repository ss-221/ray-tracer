#ifndef SPHERE_H
#define SPHERE_H

#include <hittable.h>

class sphere : public hittable
{
public:
	sphere() {}
	sphere(point3 cen, double rad, shared_ptr<material> m) : center(cen), radius(rad), matPtr(m) {}

	virtual bool hit(const ray& r, double t_min, double t_max, hitRecord& hitRec) const override;

private:
	point3 center;
	double radius = 0.0;
	shared_ptr<material> matPtr;
};

#endif // !SPHERE_H
