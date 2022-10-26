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

