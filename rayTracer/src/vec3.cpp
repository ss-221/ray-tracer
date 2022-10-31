#include "vec3.h"

double vec3::operator[](int index) const
{
    return c[index];
}

double& vec3::operator[](int index)
{
    return c[index];
}

vec3 vec3::operator-() const
{
    return vec3(-c[0], -c[1], -c[2]);
}

vec3& vec3::operator+=(const vec3& v)
{
    c[0] += v.c[0];
    c[1] += v.c[1];
    c[2] += v.c[2];

    return *this;
}

vec3& vec3::operator*=(const double t)
{
    c[0] *= t;
    c[1] *= t;
    c[2] *= t;

    return *this;
}

vec3& vec3::operator/=(const double t)
{
    return *this *= 1 / t;
}

double vec3::length() const
{
    return sqrt(sqLength());
}

double vec3::sqLength() const
{
    return c[0] * c[0] + c[1] * c[1] + c[2] * c[2];
}

bool vec3::nearZero() const
{
    const auto s = 1e-8;
    return ((fabs(c[0]) < s) && (fabs(c[1]) < s) && (fabs(c[2]) < s));
}

//Utility functions

std::ostream& operator<<(std::ostream& out, const vec3& v)
{
    return out << v.c[0] << ' ' << v.c[1] << v.c[2];
}

vec3 operator+(const vec3& v1, const vec3& v2)
{
    return vec3(v1.c[0] + v2.c[0], v1.c[1] + v2.c[1], v1.c[2] + v2.c[2]);
}

vec3 operator-(const vec3& v1, const vec3& v2)
{
    return vec3(v1.c[0] - v2.c[0], v1.c[1] - v2.c[1], v1.c[2] - v2.c[2]);
}

vec3 operator*(const vec3& v1, const vec3& v2)
{
    return vec3(v1.c[0] * v2.c[0], v1.c[1] * v2.c[1], v1.c[2] * v2.c[2]);
}

vec3 operator*(const double t, const vec3& v)
{
    return vec3(t * v.c[0], t * v.c[1], t * v.c[2]);
}


vec3 operator*(const vec3& v, const double t)
{
    return t * v;
}

vec3 operator/(const vec3& v, const double t)
{
    return v * (1 / t);
}

double dot(const vec3& v1, const vec3& v2)
{
    return  v1.c[0] * v2.c[0] + 
            v1.c[1] * v2.c[1] + 
            v1.c[2] * v2.c[2];
}

vec3 cross(const vec3& v1, const vec3& v2)
{
    return vec3(
        v1.c[1] * v2.c[2] - v1.c[2] * v2.c[1],
        v1.c[2] * v2.c[0] - v1.c[0] * v2.c[2],
        v1.c[0] * v2.c[1] - v1.c[1] * v2.c[0]);
}

vec3 unitVec(vec3 v)
{
    return v / v.length();
}

vec3 vec3::random()
{
    return vec3(randomDouble(), randomDouble(), randomDouble());
}

vec3 vec3::random(double min, double max)
{
    return vec3(randomDouble(min, max), randomDouble(min, max), randomDouble(min, max));
}

vec3 randomInUnitSphere()
{
    while (true) {
        auto p = vec3::random(-1, 1);
        if (p.sqLength() >= 1) continue;
        return p;
    }
}

vec3 randomUnitVector()
{
    return unitVec(randomInUnitSphere());
}

vec3 randomInHemisphere(const vec3& normal)
{
    vec3 inUnitSphere = randomInUnitSphere();
    if (dot(inUnitSphere, normal) > 0.0)
    {
        return inUnitSphere;
    }
    return -inUnitSphere;
}

vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2 * dot(v, n) * n;
}

vec3 refract(const vec3& uv, const vec3& n, double etaiOverEtat)
{
    auto cosTheta = fmin(dot(-uv, n), 1.0);
    vec3 rOutPerp = etaiOverEtat * (uv + cosTheta * n);
    vec3 rOutParallel = -sqrt(fabs(1.0 - rOutPerp.sqLength())) * n;

    return rOutPerp + rOutParallel;
}

vec3 randomInUnitDisk()
{
    while (true)
    {
        auto p = vec3(randomDouble(-1, 1), randomDouble(-1, 1), 0);
        if (p.sqLength() >= 1)   continue;
        return p;
    }
}