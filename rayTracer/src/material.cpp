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
	scattered = ray(rec.p, reflected + fuzz * randomInUnitSphere());
	attenuation = albedo;
	return (dot(scattered.direction(), rec.normal) > 0);
}

bool dielectric::scatter(const ray& rIn, const hitRecord& rec, colour& attenuation, ray& scattered) const
{
	attenuation = colour(1.0, 1.0, 1.0);
	double refractionRatio = rec.frontFace ? (1.0 / ir) : ir;

	vec3 unitDir = unitVec(rIn.direction());
	double cosTheta = fmin(dot(-unitDir, rec.normal), 1.0);
	double sinTheta = sqrt(1.0 - cosTheta);

	bool cannotRefract = refractionRatio * sinTheta > 1.0;
	vec3 direction;

	if (cannotRefract)
	{
		direction = reflect(unitDir, rec.normal);
	}
	else
	{
		direction = refract(unitDir, rec.normal, refractionRatio);
	}

	scattered = ray(rec.p, direction);

	return true;
}

double dielectric::reflectance(double cosine, double refIdx)
{
	auto r0 = (1 - refIdx) / (1 + refIdx);
	r0 *= r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}