#include <material.h>

bool lambertian::scatter(const ray& rIn, const hitRecord& rec, colour& attenuation, ray& scattered) const
{
	auto scatterDir = rec.normal + randomUnitVector();
	if (scatterDir.nearZero())
	{
		scatterDir = rec.normal;
	}
	scattered = ray(rec.p, scatterDir);
	attenuation = albedo;
	return true;
}

bool metal::scatter(const ray& rIn, const hitRecord& rec, colour& attenuation, ray& scattered) const
{
	vec3 reflected = reflect(unitVec(rIn.direction()), rec.normal);
	scattered = ray(rec.p, reflected);
	attenuation = albedo;
	return (dot(scattered.direction(), rec.normal) > 0);
}