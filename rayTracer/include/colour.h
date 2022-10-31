#ifndef COLOUR_H
#define COLOUR_H

#include <iostream>
#include <vec3.h>
#include <sphere.h>

double clamp(double x, double min, double max);

void writeColour(std::ostream& out, colour pixelColour, int samplesPerPixel);

colour rayColour(const ray& r, const hittable& world, int depth);

#endif // !COLOUR_H

