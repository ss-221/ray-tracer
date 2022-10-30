#include <utils.h>
#include <colour.h>
#include <hittableList.h>
#include <sphere.h>


int main(int argc, char** argv)
{
	cppLogger::Logger::setPriority(cppLogger::LoggerPriority::Debug);
	cppLogger::Logger::LogOpen("logs.txt");
	INFOMSG("Hello World!");

	point3 origin = point3(0, 0, 0);
	auto viewPortHeight = 2.0;
	auto viewPortWidth = viewPortHeight * aspectRatio;
	auto focalLen = 1.0;
	vec3 vertical = vec3(0.0, viewPortHeight, 0.0);
	vec3 horizontal = vec3(viewPortWidth, 0.0, 0.0);
	point3 lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focalLen);
	const auto imageWidth = 1920;
	const auto imageHeight = static_cast<int> (imageWidth / aspectRatio);

	hittableList world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";
	for (int j = imageHeight - 1; j >= 0; --j) {
		for (int i = 0; i < imageWidth; ++i) {

			auto u = double(i) / (imageWidth - 1);
			auto v = double(j) / (imageHeight - 1);
			ray r(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
			colour pixelColour = rayColour(r, world);
			writeColour(std::cout, pixelColour);
		}
	}
	cppLogger::Logger::LogClose();
	return 0;
}