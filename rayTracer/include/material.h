#ifndef MATERIAL_H
#define MATERIAL_H

#include <colour.h>

class material
{
public:
	virtual bool scatter(const ray& rIn, const hitRecord& rec, colour& attenuation, ray& scattered) const = 0;
};

class lambertian : public material
{
public:
	lambertian(const colour& a) : albedo(a) {}

	virtual bool scatter(const ray& rIn, const hitRecord& rec, colour& attenuation, ray& scattered) const override;

private:
	colour albedo;
};

class metal : public material
{
public:
	metal(const colour& c) : albedo(c) {}

	virtual bool scatter(const ray& rIn, const hitRecord& rec, colour& attenuation, ray& scattered) const override;

private:
	colour albedo;
};
#endif // !MATERIAL_H
