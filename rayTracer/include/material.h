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
	metal(const colour& c, double f) : albedo(c), fuzz(f) {}

	virtual bool scatter(const ray& rIn, const hitRecord& rec, colour& attenuation, ray& scattered) const override;

private:
	colour albedo;
	double fuzz;
};

class dielectric : public material
{
public:
	dielectric(double indexOfRefraction) : ir(indexOfRefraction) {}

	virtual bool scatter(const ray& rIn, const hitRecord& rec, colour& attenuation, ray& scattered) const override;

private:
	double ir;
	static double reflectance(double cosine, double refIdx);
};
#endif // !MATERIAL_H
