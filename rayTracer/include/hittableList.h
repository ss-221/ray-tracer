#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include<hittable.h>
#include<vector>
#include<memory>

using std::shared_ptr;
using std::make_shared;

class hittableList : public hittable
{
public:
	hittableList() {}
	hittableList(shared_ptr<hittable> object)
	{
		add(object);
	}
	void add(shared_ptr<hittable> object)
	{
		objects.push_back(object);
	}
	void clear()
	{
		objects.clear();
	}

	virtual bool hit(const ray& r, double t_min, double t_max, hitRecord& hitRec) const override;

private:
	std::vector<shared_ptr<hittable>> objects;


};


#endif // !HITTABLE_LIST_H

