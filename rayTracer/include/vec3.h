#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <ostream>

constexpr int DIMENSIONS = 3;

class vec3 {

public:
	vec3() : c{ 0, 0, 0 } {}
	vec3(double x, double y, double z) : c{ x, y, z } {}
	double x() const { return c[0]; }
	double y() const { return c[1]; }
	double z() const { return c[2]; }

	double operator[](int index) const;
	double& operator[](int index);
	vec3 operator-() const;
	vec3& operator+=(const vec3& v);
	vec3& operator*=(const double t);
	vec3& operator/=(const double t);
	double length() const;
	double sqLength() const;

	friend std::ostream& operator<<(std::ostream& out, const vec3& v);
	friend vec3 operator+(const vec3& v1, const vec3& v2);
	friend vec3 operator-(const vec3& v1, const vec3& v2);
	friend vec3 operator*(const vec3& v1, const vec3& v2);
	friend vec3 operator*(const double t, const vec3& v);
	friend vec3 operator*(const vec3& v, const double t);
	friend vec3 operator/(const vec3& v, const double t);
	friend double dot(const vec3& v1, const vec3& v2);
	friend vec3 cross(const vec3& v1, const vec3& v2);
	friend vec3 unitVec(vec3 v);

private:
	double c[DIMENSIONS];
};

using colour = vec3;
using point3 = vec3;
#endif // !VEC3_H