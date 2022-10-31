#include <sphere.h>

bool sphere::hit(const ray& r, double t_min, double t_max, hitRecord& hitRec) const
{
	vec3 adjustedCenter = r.origin() - center;
	auto a = r.direction().sqLength();
	auto halfB = dot(adjustedCenter, r.direction());
	auto c = adjustedCenter.sqLength() - radius * radius;

	auto discriminant = halfB * halfB - a * c;

	if (discriminant < 0)	return false;

	auto sqrtDiscriminant = sqrt(discriminant);

	auto root = (-halfB - sqrtDiscriminant) / a;

	if (root < t_min || t_max < root)
	{
		root = (-halfB + sqrtDiscriminant) / a;

		if (root < t_min || t_max < root)
		{
			return false;
		}
	}

	hitRec.t = root;
	hitRec.p = r.at(hitRec.t);
	vec3 outwardNormal = (hitRec.p - center) / radius;
	hitRec.setFaceNormal(r, outwardNormal);
	hitRec.matPtr = matPtr;

	return true;
}
