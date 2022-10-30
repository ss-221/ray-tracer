#include "hittableList.h"

bool hittableList::hit(const ray& r, double t_min, double t_max, hitRecord& hitRec) const
{
	hitRecord tempRec;
	bool hitAnything = false;
	auto closestSoFar = t_max;

	for (const auto& obj : objects)
	{
		if (obj->hit(r, t_min, closestSoFar, tempRec))
		{
			hitAnything = true;
			closestSoFar = tempRec.t;
			hitRec = tempRec;
		}
	}

	return hitAnything;
}
