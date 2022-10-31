#include <utils.h>
#include <hittableList.h>
#include <sphere.h>
#include <camera.h>
#include <material.h>

int main(int argc, char** argv)
{
	cppLogger::Logger::LogOpen("logs.txt");

	const auto aspectRatio = 16.0 / 9.0;
	const auto imageWidth = 1920;
	const auto imageHeight = static_cast<int> (imageWidth / aspectRatio);
	const int samplesPerPixel = 100;
	const int maxDepth = 50;
	INFOMSG("Resolution: %d x %d", imageWidth, imageHeight);

	auto R = cos(PI / 4);
	hittableList world;

	auto material_ground = make_shared<lambertian>(colour(0.8, 0.8, 0.0));
	auto material_center = make_shared<lambertian>(colour(0.1, 0.2, 0.5));
	auto material_left = make_shared<dielectric>(1.5);
	auto material_right = make_shared<metal>(colour(0.8, 0.6, 0.2), 0.0);

	world.add(make_shared<sphere>(point3(0.0, -100.5, -1.0), 100.0, material_ground));
	world.add(make_shared<sphere>(point3(0.0, 0.0, -1.0), 0.5, material_center));
	world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), 0.5, material_left));
	world.add(make_shared<sphere>(point3(-1.0, 0.0, -1.0), -0.45, material_left));
	world.add(make_shared<sphere>(point3(1.0, 0.0, -1.0), 0.5, material_right));

	camera cam(point3(-2, 2, 1), point3(0, 0, -1), vec3(0, 1, 0), 90, aspectRatio);
	

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
	for (int j = imageHeight - 1; j >= 0; --j) {
		for (int i = 0; i < imageWidth; ++i) {

			colour pixelColour(0, 0, 0);

			for (int s = 0; s < samplesPerPixel; ++s)
			{
				auto u = (i + randomDouble()) / (imageWidth - 1);
				auto v = (j + randomDouble()) / (imageHeight - 1);
				ray r = cam.getRay(u, v);
				pixelColour += rayColour(r, world, maxDepth);
			}
			writeColour(std::cout, pixelColour, samplesPerPixel);
		}
	}
	cppLogger::Logger::LogClose();
	return 0;
}