#include <utils.h>
#include <hittableList.h>
#include <sphere.h>
#include <camera.h>
#include <material.h>

hittableList randomScene()
{
	hittableList world;

	auto groundMaterial = make_shared<lambertian>(colour(0.5, 0.5, 0.5));
	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, groundMaterial));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = randomDouble();
			point3 center(a + 0.9 * randomDouble(), 0.2, b + 0.9 * randomDouble());

			if ((center - point3(4, 0.2, 0)).length() > 0.9) {
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					auto albedo = vec3::random() * vec3::random();
					sphere_material = make_shared<lambertian>(albedo);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					auto albedo = vec3::random(0.5, 1);
					auto fuzz = randomDouble(0, 0.5);
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = make_shared<dielectric>(1.5);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<lambertian>(colour(0.4, 0.2, 0.1));
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(colour(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	return world;
}


void RenderImage(const int& imageHeight, const int& imageWidth, const int& samplesPerPixel, const int& maxDepth, const camera& cam, const hittableList& world, std::ofstream& imageFile)
{
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
			writeColour(imageFile, pixelColour, samplesPerPixel);
		}
	}
}

int main(int argc, char** argv)
{
	cppLogger::Logger::LogOpen("logs.txt");

	//Image Details
	const auto aspectRatio = 16.0 / 9.0;
	const auto imageWidth = 1920;
	const auto imageHeight = static_cast<int> (imageWidth / aspectRatio);
	const int samplesPerPixel = 50;
	const int maxDepth = 50;
	INFOMSG("Resolution: %d x %d", imageWidth, imageHeight);

	//Setting the scene
	auto world = randomScene();

	//Camera Details
	point3 lookFrom(13, 2, 3);
	point3 lookAt(0, 0, 0);
	vec3 viewUp(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;

	camera cam(lookFrom, lookAt, viewUp, 20, aspectRatio, aperture, dist_to_focus);

	//Rendering
	std::ofstream imageFile;
	imageFile.open("image.ppm", std::ios::binary);

	imageFile << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

	RenderImage(imageHeight, imageWidth, samplesPerPixel, maxDepth, cam, world, imageFile);

	imageFile.close();
	cppLogger::Logger::LogClose();
	return 0;
}