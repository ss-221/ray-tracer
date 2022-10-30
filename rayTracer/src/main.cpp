#include <utils.h>
#include <colour.h>
#include <hittableList.h>
#include <sphere.h>
#include <camera.h>


int main(int argc, char** argv)
{
	cppLogger::Logger::LogOpen("logs.txt");

	const auto imageWidth = 1920;
	const auto imageHeight = static_cast<int> (imageWidth / aspectRatio);
	const int samplesPerPixel = 100;
	INFOMSG("Resolution: %d x %d", imageWidth, imageHeight);

	camera cam;
	hittableList world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));
	const int maxDepth = 50;

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